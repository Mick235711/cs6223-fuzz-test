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
#define FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

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
