#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include <range/v3/all.hpp>
#include <ranges>
#ifdef USE_RANGE_V3
namespace ranges_use = ::ranges;
namespace views_use = ::ranges::views;
#else
namespace ranges_use = ::std::ranges;
namespace views_use = ::std::views;
#endif
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#define FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

using namespace fuzztest;

template<typename T>
void test_empty()
{
    auto v = views_use::empty<T>;
    EXPECT_EQ(ranges_use::size(v), 0);
    EXPECT_EQ(ranges_use::distance(v), 0);
    EXPECT_EQ(ranges_use::begin(v), ranges_use::end(v));
}
TEST(MyTestSuite, empty) {
    test_empty<int>(); test_empty<std::string>();
    test_empty<std::vector<int>>();
}
// no fuzz test because no values

void test_single(const auto& value)
{
    auto v = views_use::single(value);
    EXPECT_EQ(ranges_use::size(v), 1);
    EXPECT_EQ(ranges_use::distance(v), 1);
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    EXPECT_EQ(ranges_use::distance(beg, end), 1);
    EXPECT_EQ(ranges_use::next(beg, 1), end);
    EXPECT_EQ(beg + 1, end); EXPECT_EQ(end - 1, beg);
    EXPECT_EQ(end - beg, 1);
    EXPECT_EQ(*beg, value);
}
TEST(MyTestSuite, single) {
    test_single(2ull); test_single("44525");
    test_single(std::vector{1uz, 2uz, 3uz});
}

void test_single_int(int value) { test_single(value); }
void test_single_str(const std::string& str) { test_single(str); }
void test_single_vec(const std::vector<int>& vec) { test_single(vec); }
FUZZ_TEST(MyTestSuite, test_single_int);
FUZZ_TEST(MyTestSuite, test_single_str);
FUZZ_TEST(MyTestSuite, test_single_vec);

void test_iota_inf(int a)
{
    auto v = views_use::iota(a);
    auto beg = ranges_use::begin(v);
    EXPECT_EQ(*beg, a);
    if (a < std::numeric_limits<int>::max() - 1000)
    {
        EXPECT_EQ(*(beg + 1000), a + 1000);
        ranges_use::advance(beg, 100);
        EXPECT_EQ(*beg, a + 100);
        EXPECT_EQ(*(beg - 10), a + 90);
    }
}
void test_iota(int a, int b)
{
    if (a > b) return;
    auto v = views_use::iota(a, b);
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    EXPECT_EQ(*beg, a);
    for (int i = 0; beg != end; ++beg, ++i)
    {
        EXPECT_EQ(*beg, a + i);
    }
}
TEST(MyTestSuite, iota) {
    test_iota_inf(0);
    test_iota(1, -1);
    test_iota(1, 100);
}
FUZZ_TEST(MyTestSuite, test_iota_inf);
FUZZ_TEST(MyTestSuite, test_iota);

#ifndef USE_RANGE_V3
void test_istream(const std::vector<int>& vec)
{
    std::ostringstream os;
    for (auto a : vec) os << a << " ";
    auto str = os.str();
    std::istringstream is{str};
    auto v = views_use::istream<int>(is);
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (int i = 0; beg != end; ++beg, ++i)
    {
        EXPECT_LT(i, vec.size());
        EXPECT_EQ(*beg, vec[i]);
    }
}
TEST(MyTestSuite, istream) {
    test_istream({2, 3, -2, 65, 1, 0});
}
FUZZ_TEST(MyTestSuite, test_istream);
#endif

void test_filter_simple(const std::vector<int>& vec, std::pair<int, int> mod_upper)
{
    auto [mod, upper] = mod_upper;
    auto v = vec | views_use::filter([=](auto a) { return a % mod < upper; });
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (auto a : vec)
    {
        if (a % mod < upper)
        {
            EXPECT_NE(beg, end);
            EXPECT_EQ(*beg, a);
            ++beg;
        }
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, filter) {
    test_filter_simple({2, 3, 65, 0, 2, 1}, std::pair{2, 1});
}
Domain<std::pair<int, int>> PairDomain()
{
    // domain where 0 <= b <= a
    auto inner = [](int a) { return PairOf(Just(a), InRange(0, a)); };
    return FlatMap(inner, InRange(2, std::numeric_limits<int>::max()));
}
FUZZ_TEST(MyTestSuite, test_filter_simple)
    .WithDomains(Arbitrary<std::vector<int>>(), PairDomain());

void test_transform_simple(const std::deque<int>& vec)
{
    auto v = vec | views_use::transform([=](auto a) { auto s = std::to_string(a); return s + s; });
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (auto a : vec)
    {
        EXPECT_NE(beg, end);
        auto s = std::to_string(a);
        EXPECT_EQ(*beg, s + s);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, transform) {
    test_transform_simple({2, 3, 65, 0, 2, 1, -5, -7});
}
FUZZ_TEST(MyTestSuite, test_transform_simple);

void test_take(const std::list<int>& vec, std::size_t fst)
{
    auto v = vec | views_use::take(fst);
    auto sz = std::min(fst, ranges_use::size(vec));
    EXPECT_EQ(ranges_use::size(v), sz);
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    int i = 0;
    for (auto a : vec)
    {
        if (++i > fst) break;
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, a);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, take) {
    test_take({2, 3, 65, 0, 2, 1, -5, -7}, 4);
    test_take({2, 3, 65, 0, 2, 1, -5, -7}, 40);
}
FUZZ_TEST(MyTestSuite, test_take).WithDomains(Arbitrary<std::list<int>>(), NonNegative<int>());

void test_take_while(const std::list<int>& vec, int upp)
{
    auto v = vec | views_use::take_while([=](auto a) { return a < upp; });
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    int i = 0;
    for (auto a : vec)
    {
        if (a >= upp) break;
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, a);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, take_while) {
    test_take_while({2, 3, 65, 0, 2, 1, -5, -7}, 4);
    test_take_while({2, 3, 65, 0, 2, 1, -5, -7}, -40);
}
FUZZ_TEST(MyTestSuite, test_take_while);

void test_drop(const std::list<int>& vec, std::size_t fst)
{
    auto v = vec | views_use::drop(fst);
    auto sz = fst < ranges_use::size(vec) ? ranges_use::size(vec) - fst : 0uz;
    EXPECT_EQ(ranges_use::size(v), sz);
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    int i = 0;
    for (auto a : vec)
    {
        if (++i <= fst) continue;
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, a);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, drop) {
    test_drop({2, 3, 65, 0, 2, 1, -5, -7}, 4);
    test_drop({2, 3, 65, 0, 2, 1, -5, -7}, 40);
}
FUZZ_TEST(MyTestSuite, test_drop).WithDomains(Arbitrary<std::list<int>>(), NonNegative<int>());

void test_drop_while(const std::list<int>& vec, int upp)
{
    auto v = vec | views_use::drop_while([=](auto a) { return a < upp; });
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    int i = 0;
    bool flag = false;
    for (auto a : vec)
    {
        if (!flag && a < upp) continue;
        flag = true;
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, a);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, drop_while) {
    test_drop_while({2, 3, 65, 0, 2, 1, -5, -7}, 4);
    test_drop_while({2, 3, 65, 0, 2, 1, -5, -7}, -40);
}
FUZZ_TEST(MyTestSuite, test_drop_while);

// join not implemented in libc++
#ifdef USE_RANGE_V3
void test_join(const std::set<std::vector<int>>& vec)
{
    auto v = vec | views_use::join;
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (auto a : vec) for (auto b : a)
    {
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, b);
        ++beg;
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, join) {
    test_join({std::vector<int>{2, 3}, std::vector<int>{}, std::vector<int>{45, -1, -2}});
}
FUZZ_TEST(MyTestSuite, test_join);
#endif

// TODO: libc++ bug, vec | views::split does not work
#ifndef USE_RANGE_V3
void test_lazy_split(const std::string& vec)
{
    auto v = views_use::lazy_split(vec, "|");
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    std::string res;
    bool first = true;
    for (; beg != end; ++beg)
    {
        if (!first) res += "|";
        else first = false;
        for (auto ch : *beg) res += ch;
    }
    EXPECT_EQ(res, vec);
}
TEST(MyTestSuite, lazy_split) {
    test_lazy_split("a||b|cresgwe|deqevEW|e");
}
FUZZ_TEST(MyTestSuite, test_lazy_split).WithDomains(StringOf(OneOf(Just('|'), NonZeroChar())));
#endif

void test_split(const std::string& vec)
{
    auto v = views_use::split(vec, "|");
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    std::string res;
    bool first = true;
    for (; beg != end; ++beg)
    {
        if (!first) res += "|";
        else first = false;
        for (auto ch : *beg) res += ch;
    }
    EXPECT_EQ(res, vec);
}
TEST(MyTestSuite, split) {
    test_split("a||b|cresgwe|deqevEW|e");
}
FUZZ_TEST(MyTestSuite, test_split).WithDomains(StringOf(OneOf(Just('|'), NonZeroChar())));

void test_reverse(const std::vector<std::string>& vec)
{
    auto v = vec | views_use::reverse;
    EXPECT_EQ(ranges_use::size(v), ranges_use::size(vec));
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (int i = int(vec.size()) - 1; i >= 0; --i)
    {
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, vec[i]);
        ++beg;
    }
    EXPECT_EQ(beg, end);

    beg = ranges_use::begin(v);
    end = ranges_use::end(v);
    for (auto a : vec)
    {
        EXPECT_NE(beg, end);
        --end;
        EXPECT_EQ(*end, a);
    }
    EXPECT_EQ(beg, end);
}
TEST(MyTestSuite, reverse) {
    test_reverse({"frwneo23r", "", "r24 e2 ", " 4r "});
}
FUZZ_TEST(MyTestSuite, test_reverse);

#ifndef USE_RANGE_V3
void test_elements(const std::map<int, std::string>& vec)
{
    auto v = vec | views_use::elements<0>;
    EXPECT_EQ(ranges_use::size(v), ranges_use::size(vec));
    auto beg = ranges_use::begin(v);
    auto end = ranges_use::end(v);
    for (const auto& [key, val] : vec)
    {
        EXPECT_NE(beg, end);
        EXPECT_EQ(*beg, key);
        ++beg;
    }
    EXPECT_EQ(beg, end);

    auto v2 = vec | views_use::elements<1>;
    auto beg2 = ranges_use::begin(v2);
    auto end2 = ranges_use::end(v2);
    for (const auto& [key, val] : vec)
    {
        EXPECT_NE(beg2, end2);
        EXPECT_EQ(*beg2, val);
        ++beg2;
    }
    EXPECT_EQ(beg2, end2);
}
TEST(MyTestSuite, elements) {
    test_elements({{2, "frwneo23r"}, {-1, ""}, {0, "r24 e2 "}, {3, " 4r "}});
}
FUZZ_TEST(MyTestSuite, test_elements);
#endif
