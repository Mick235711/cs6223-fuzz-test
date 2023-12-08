#include "range_property.hpp"
#include "gtest/gtest.h"
#include <vector>
#include <set>
#include <string>
#include <type_traits>
#include <list>
#include <forward_list>
#include <ranges>
#include "demangle.hpp"
#define FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
namespace ranges = std::ranges;
namespace views = std::views;

void test_with_ranges(auto F)
{
    F(std::vector<int>{});
    F(std::vector{3.5, 2.4, 5.3});
    F(std::vector<std::string>{"Hello", "World"});
    std::vector<int> vec1{}; F(std::as_const(vec1)); F(vec1);
    std::vector vec2{3.5, 2.4, 5.3}; F(std::as_const(vec2)); F(vec2);
    std::vector<std::string> vec3{"Hello", "World"}; F(std::as_const(vec3)); F(vec3);
    F(std::set<int>{});
    F(std::set{3.5, 2.4, 5.3});
    F(std::set<std::string>{"Hello", "World"});
    std::set<int> s1{}; F(std::as_const(s1)); F(s1);
    std::set s2{3.5, 2.4, 5.3}; F(std::as_const(s2)); F(s2);
    std::set<std::string> s3{"Hello", "World"}; F(std::as_const(s3)); F(s3);
    F(std::list<int>{});
    F(std::forward_list<double>{});
    F(vec2 | views::take_while([](auto a) { return a > 3; })); // uncommon, unsized range
}

template<typename T>
inline constexpr bool is_deep_const_v = !std::is_reference_v<T> || std::is_const_v<std::remove_reference_t<T>>;
template<typename T>
inline constexpr bool is_deep_volatile_v = !std::is_reference_v<T> || std::is_volatile_v<std::remove_reference_t<T>>;

TEST(MyTestSuite, ReferenceTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = ref_remove_all(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE((std::is_same_v<ranges::range_reference_t<R1>, std::remove_cvref_t<ranges::range_reference_t<R1>>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_reference_t<R1>>());
        auto r2 = ref_add_const(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE((is_deep_const_v<ranges::range_reference_t<R2>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_reference_t<R2>>());
        auto r3 = ref_add_volatile(FWD(R)); using R3 = std::remove_cvref_t<decltype(r3)>;
        EXPECT_TRUE((is_deep_volatile_v<ranges::range_reference_t<R3>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_reference_t<R3>>());
        auto r4 = ref_add_lref(FWD(R)); using R4 = std::remove_cvref_t<decltype(r4)>;
        EXPECT_TRUE((std::is_lvalue_reference_v<ranges::range_reference_t<R4>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_reference_t<R4>>());
        auto r5 = ref_add_rref(FWD(R)); using R5 = std::remove_cvref_t<decltype(r5)>;
        EXPECT_TRUE((std::is_rvalue_reference_v<ranges::range_reference_t<R5>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_reference_t<R5>>());
    });
}

TEST(MyTestSuite, ValueTypeTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = val_remove_all(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE((std::is_same_v<ranges::range_value_t<R1>, std::remove_cvref_t<ranges::range_value_t<R1>>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_value_t<R1>>());
        auto r2 = val_add_const(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE((is_deep_const_v<ranges::range_value_t<R2>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_value_t<R2>>());
        auto r3 = val_add_volatile(FWD(R)); using R3 = std::remove_cvref_t<decltype(r3)>;
        EXPECT_TRUE((is_deep_volatile_v<ranges::range_value_t<R3>>))
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_value_t<R3>>());
    });
}

TEST(MyTestSuite, CategoryTests) {
    test_with_ranges([](auto&& R) {
        using Range = std::remove_cvref_t<decltype(R)>;
        if constexpr (ranges::input_range<Range>) {
            auto r1 = decay_to_lower<std::input_iterator_tag>(FWD(R)); using R1 = ranges::iterator_t<std::remove_cvref_t<decltype(r1)>>;
            EXPECT_TRUE((std::is_same_v<iter_category<R1>, std::input_iterator_tag>))
                << (type_str<decltype(R)>() + " -> " + type_str<iter_category<R1>>());
        }
        /*if constexpr (ranges::output_range<Range, ranges::range_value_t<Range>>) {
            auto r2 = decay_to_lower<std::output_iterator_tag>(FWD(R)); using R2 = ranges::iterator_t<std::remove_cvref_t<decltype(r2)>>;
            EXPECT_TRUE((std::is_same_v<iter_category<R2>, std::output_iterator_tag>))
                << (type_str<decltype(R)>() + " -> " + type_str<iter_category<R2>>());
        }*/
        if constexpr (ranges::forward_range<Range>) {
            auto r3 = decay_to_lower<std::forward_iterator_tag>(FWD(R)); using R3 = ranges::iterator_t<std::remove_cvref_t<decltype(r3)>>;
            EXPECT_TRUE((std::is_same_v<iter_category<R3>, std::forward_iterator_tag>))
                << (type_str<decltype(R)>() + " -> " + type_str<iter_category<R3>>());
        }
        if constexpr (ranges::bidirectional_range<Range>) {
            auto r4 = decay_to_lower<std::bidirectional_iterator_tag>(FWD(R)); using R4 = ranges::iterator_t<std::remove_cvref_t<decltype(r4)>>;
            EXPECT_TRUE((std::is_same_v<iter_category<R4>, std::bidirectional_iterator_tag>))
                << (type_str<decltype(R)>() + " -> " + type_str<iter_category<R4>>());
        }
        if constexpr (ranges::random_access_range<Range>) {
            auto r5 = decay_to_lower<std::random_access_iterator_tag>(FWD(R)); using R5 = ranges::iterator_t<std::remove_cvref_t<decltype(r5)>>;
            EXPECT_TRUE((std::is_same_v<iter_category<R5>, std::random_access_iterator_tag>))
                << (type_str<decltype(R)>() + " -> " + type_str<iter_category<R5>>());
        }
    });
}

TEST(MyTestSuite, CommonTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = to_uncommon(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE(!ranges::common_range<R1>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R1>>() + " to " + type_str<ranges::sentinel_t<R1>>());
        auto r2 = to_common(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE(ranges::common_range<R2>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R2>>() + " to " + type_str<ranges::sentinel_t<R2>>());
    });
}

TEST(MyTestSuite, SizedTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = to_unsized(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE(!ranges::sized_range<R1>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R1>>() + " to " + type_str<ranges::sentinel_t<R1>>());
        auto r2 = to_sized(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE(ranges::sized_range<R2>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R2>>() + " to " + type_str<ranges::sentinel_t<R2>>());
    });
}

TEST(MyTestSuite, ConstIterableTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = to_unconst_iterable(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE(!ranges::range<const R1>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R1>>() + " to " + type_str<ranges::sentinel_t<R1>>());
        auto r2 = to_const_iterable(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE(ranges::range<const R2>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R2>>() + " to " + type_str<ranges::sentinel_t<R2>>());
    });
}

TEST(MyTestSuite, BorrowedTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = to_unborrowed(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE(!ranges::borrowed_range<R1>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R1>>() + " to " + type_str<ranges::sentinel_t<R1>>());
        auto r2 = to_borrowed(FWD(R)); using R2 = std::remove_cvref_t<decltype(r2)>;
        EXPECT_TRUE(ranges::borrowed_range<R2>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::iterator_t<R2>>() + " to " + type_str<ranges::sentinel_t<R2>>());
    });
}

TEST(MyTestSuite, ConstantTests) {
    test_with_ranges([](auto&& R) {
        auto r1 = to_constant(FWD(R)); using R1 = std::remove_cvref_t<decltype(r1)>;
        EXPECT_TRUE(view_future::constant_range<R1>)
            << (type_str<decltype(R)>() + " -> " + type_str<ranges::range_value_t<R1>>() + " + " + type_str<ranges::range_reference_t<R1>>());
    });
}
