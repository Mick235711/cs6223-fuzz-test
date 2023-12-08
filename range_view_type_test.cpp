#include "gtest/gtest.h"
#include <cstdio>
#include <range/v3/all.hpp>
namespace ranges_v3 = ::ranges;
namespace views_v3 = ::ranges::views;
#include "range_property.hpp"
namespace ranges_std = ::std::ranges;
namespace views_std = ::std::views;
#include "random_ranges.hpp"
#include "demangle.hpp"
#define FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

template<typename RR> struct test_all_aux;
template<typename... Ranges>
struct test_all_aux<typelist<Ranges...>>
{
    static void call(auto F)
    {
        (F.template operator()<Ranges>(), ...);
    }
};

int total_count, err_count;

template<typename TList = random_ranges>
void test_all(auto F)
{
    total_count = 0; err_count = 0;
    test_all_aux<TList>::call(std::move(F));
    std::printf("Total: %d, Error: %d\n", total_count, err_count);
}

#ifdef COUNT_ERROR
#define EXPECT_SAME(T, R1, ...) \
    ++total_count; \
    if (!std::is_same_v<R1, __VA_ARGS__>) ++err_count
#define EXPECT_EQAL(T, R1, ...) \
    ++total_count; \
    if ((R1) != (__VA_ARGS__)) ++err_count
#define EXPECT_HOLD(T, ...) \
    ++total_count; \
    if (!(__VA_ARGS__)) ++err_count
#else
#define EXPECT_SAME(T, R1, ...) \
    EXPECT_TRUE((std::is_same_v<R1, __VA_ARGS__>)) \
        << type_str<T>() << " -> " << type_str<R1>() << " => " << type_str<__VA_ARGS__>()
#define EXPECT_EQAL(T, R1, ...) \
    EXPECT_EQ(R1, __VA_ARGS__) << type_str<T>()
#define EXPECT_HOLD(T, ...) \
    EXPECT_TRUE((__VA_ARGS__)) << type_str<T>()
#endif

TEST(MyTestSuite, empty_std) {
    test_all([]<typename T>() {
        auto v = views_std::empty<T>;
        using V = decltype(v);
        EXPECT_SAME(T, ranges_std::range_reference_t<V>, T&);
        EXPECT_SAME(T, ranges_std::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_std::contiguous_range<V>);
        EXPECT_HOLD(T, ranges_std::common_range<V>);
        EXPECT_HOLD(T, ranges_std::sized_range<V>);
        EXPECT_EQAL(T, ranges_std::size(v), 0);
        EXPECT_HOLD(T, ranges_std::range<const V>);
        EXPECT_HOLD(T, ranges_std::borrowed_range<V>);
        EXPECT_EQAL(T, view_future::constant_range<V>, std::is_const_v<T>);
    });
}

// do not try to evaluate constant range for v3 types
TEST(MyTestSuite, empty_v3) {
    test_all([]<typename T>() {
        auto v = views_v3::empty<T>;
        using V = decltype(v);
        EXPECT_SAME(T, ranges_v3::range_reference_t<V>, T&);
        EXPECT_SAME(T, ranges_v3::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_v3::contiguous_range<V>);
        EXPECT_HOLD(T, ranges_v3::common_range<V>);
        EXPECT_HOLD(T, ranges_v3::sized_range<V>);
        EXPECT_EQAL(T, ranges_v3::size(v), 0);
        EXPECT_HOLD(T, ranges_v3::range<const V>);
        EXPECT_HOLD(T, ranges_v3::borrowed_range<V>);
    });
}

TEST(MyTestSuite, single_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T>) {
            auto v = views_std::single(T{});
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, T&);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, T);
            EXPECT_HOLD(T, ranges_std::contiguous_range<V>);
            EXPECT_HOLD(T, ranges_std::common_range<V>);
            EXPECT_HOLD(T, ranges_std::sized_range<V>);
            EXPECT_EQAL(T, ranges_std::size(v), 1);
            EXPECT_HOLD(T, ranges_std::range<const V>);
            EXPECT_HOLD(T, !ranges_std::borrowed_range<V>);
            EXPECT_HOLD(T, !view_future::constant_range<V>);
        }
    });
}

TEST(MyTestSuite, single_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            auto v = views_v3::single(T{});
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, T&);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, T);
            EXPECT_HOLD(T, ranges_v3::contiguous_range<V>);
            EXPECT_HOLD(T, ranges_v3::common_range<V>);
            EXPECT_HOLD(T, ranges_v3::sized_range<V>);
            EXPECT_EQAL(T, ranges_v3::size(v), 1);
            EXPECT_HOLD(T, ranges_v3::range<const V>);
            EXPECT_HOLD(T, !ranges_v3::borrowed_range<V>);
        }
    });
}

using arithmetics = typelist<short, unsigned short, int, unsigned int, char, signed char, unsigned char,
      long, unsigned long, long long, unsigned long long, std::size_t>;
TEST(MyTestSuite, iota_std_inf) {
    test_all<arithmetics>([]<typename T>() {
        auto v = views_std::iota(T(0));
        using V = decltype(v);
        EXPECT_SAME(T, ranges_std::range_reference_t<V>, T);
        EXPECT_SAME(T, ranges_std::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_std::random_access_range<V>);
        EXPECT_HOLD(T, !ranges_std::common_range<V>);
        EXPECT_HOLD(T, !ranges_std::sized_range<V>);
        EXPECT_HOLD(T, ranges_std::range<const V>);
        EXPECT_HOLD(T, ranges_std::borrowed_range<V>);
        EXPECT_HOLD(T, view_future::constant_range<V>);
    });
}

// Detects existing issue: https://github.com/llvm/llvm-project/issues/67551
// remove char and short from arithmetics
using arithmetics2 = typelist<int, unsigned int,
      long, unsigned long, long long, unsigned long long, std::size_t>;
TEST(MyTestSuite, iota_std_bound) {
    test_all<arithmetics2>([]<typename T>() {
        auto v = views_std::iota(T(0), T(10));
        using V = decltype(v);
        EXPECT_SAME(T, ranges_std::range_reference_t<V>, T);
        EXPECT_SAME(T, ranges_std::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_std::random_access_range<V>);
        EXPECT_HOLD(T, ranges_std::common_range<V>);
        EXPECT_HOLD(T, ranges_std::sized_range<V>);
        EXPECT_EQAL(T, ranges_std::size(v), T(10));
        EXPECT_HOLD(T, ranges_std::range<const V>);
        EXPECT_HOLD(T, ranges_std::borrowed_range<V>);
        EXPECT_HOLD(T, view_future::constant_range<V>);
    });
}

TEST(MyTestSuite, iota_std_diff) {
    test_all<arithmetics>([]<typename T>() {
        if constexpr (!std::is_same_v<double, T>) {
            auto v = views_std::iota(T(0), double(10));
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, T);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, T);
            EXPECT_HOLD(T, ranges_std::random_access_range<V>);
            EXPECT_HOLD(T, !ranges_std::common_range<V>);
            EXPECT_HOLD(T, !ranges_std::sized_range<V>);
            EXPECT_HOLD(T, ranges_std::range<const V>);
            EXPECT_HOLD(T, ranges_std::borrowed_range<V>);
            EXPECT_HOLD(T, view_future::constant_range<V>);
        }
    });
}

TEST(MyTestSuite, iota_v3_inf) {
    test_all<arithmetics>([]<typename T>() {
        auto v = views_v3::iota(T(0));
        using V = decltype(v);
        EXPECT_SAME(T, ranges_v3::range_reference_t<V>, T);
        EXPECT_SAME(T, ranges_v3::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_v3::random_access_range<V>);
        EXPECT_HOLD(T, !ranges_v3::common_range<V>);
        EXPECT_HOLD(T, !ranges_v3::sized_range<V>);
        EXPECT_HOLD(T, ranges_v3::range<const V>);
        EXPECT_HOLD(T, ranges_v3::borrowed_range<V>);
    });
}

TEST(MyTestSuite, iota_v3_bound) {
    test_all<arithmetics>([]<typename T>() {
        auto v = views_v3::iota(T(0), T(10));
        using V = decltype(v);
        EXPECT_SAME(T, ranges_v3::range_reference_t<V>, T);
        EXPECT_SAME(T, ranges_v3::range_value_t<V>, T);
        EXPECT_HOLD(T, ranges_v3::random_access_range<V>);
        EXPECT_HOLD(T, ranges_v3::common_range<V>);
        EXPECT_HOLD(T, ranges_v3::sized_range<V>);
        EXPECT_EQAL(T, ranges_v3::size(v), T(10));
        EXPECT_HOLD(T, ranges_v3::range<const V>);
        EXPECT_HOLD(T, ranges_v3::borrowed_range<V>);
    });
}

TEST(MyTestSuite, iota_v3_diff) {
    test_all<arithmetics>([]<typename T>() {
        if constexpr (!std::is_same_v<double, T>) {
            auto v = views_v3::iota(T(0), double(10));
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, T);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, T);
            EXPECT_HOLD(T, ranges_v3::random_access_range<V>);
            EXPECT_HOLD(T, !ranges_v3::common_range<V>);
            EXPECT_HOLD(T, !ranges_v3::sized_range<V>);
            EXPECT_HOLD(T, ranges_v3::range<const V>);
            EXPECT_HOLD(T, ranges_v3::borrowed_range<V>);
        }
    });
}

TEST(MyTestSuite, counted_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T>) {
            T t;
            auto v = views_std::counted(ranges_std::begin(t), 0);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::random_access_range<T>);
            EXPECT_HOLD(T, ranges_std::sized_range<V>);
            EXPECT_EQAL(T, ranges_std::size(v), 0);
            EXPECT_HOLD(T, ranges_std::range<const V>);
            EXPECT_HOLD(T, ranges_std::borrowed_range<V>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

TEST(MyTestSuite, counted_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T>) {
            T t;
            auto v = views_v3::counted(ranges_v3::begin(t), 0);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::random_access_range<T>);
            EXPECT_HOLD(T, ranges_v3::sized_range<V>);
            EXPECT_EQAL(T, ranges_v3::size(v), 0);
            EXPECT_HOLD(T, ranges_v3::range<const V>);
            EXPECT_HOLD(T, ranges_v3::borrowed_range<V>);
        }
    });
}

// don't test borrowed and const-iterable since ref_view is always those
TEST(MyTestSuite, all_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::all(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::common_range<T>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

TEST(MyTestSuite, all_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::all(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::common_range<T>);
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
        }
    });
}

template<typename A, typename B>
requires std::derived_from<A, B> || std::derived_from<B, A>
using clamp_down = std::conditional_t<
    std::is_base_of_v<A, B>, A, B>;

TEST(MyTestSuite, filter_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::filter(t, [](auto&& a) { return true; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::bidirectional_iterator_tag>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::common_range<T>);
            EXPECT_HOLD(T, !ranges_std::sized_range<V>);
            EXPECT_HOLD(T, !ranges_std::borrowed_range<V>);
            EXPECT_HOLD(T, !ranges_std::range<const V>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

TEST(MyTestSuite, filter_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::filter(t, [](auto&& a) { return true; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::bidirectional_iterator_tag>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::common_range<T>);
            EXPECT_HOLD(T, !ranges_v3::sized_range<V>);
            EXPECT_HOLD(T, !ranges_v3::borrowed_range<V>);
            EXPECT_HOLD(T, !ranges_v3::range<const V>);
        }
    });
}

TEST(MyTestSuite, transform_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::transform(t, [](auto&& a) { return 1; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, int);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, int);
#ifdef COUNT_ERROR
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::random_access_iterator_tag>);
#endif
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::common_range<T>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
            EXPECT_HOLD(T, !ranges_std::borrowed_range<V>);
            EXPECT_HOLD(T, view_future::constant_range<V>);
        }
    });
}

// TODO: find bugs here
TEST(MyTestSuite, transform_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::transform(t, [](auto&& a) { return 1; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, int);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, int);
#ifdef COUNT_ERROR
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::random_access_iterator_tag>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::common_range<T>);
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
            EXPECT_HOLD(T, !ranges_v3::borrowed_range<V>);
        }
    });
}

TEST(MyTestSuite, take_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::take(t, 10);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::sized_range<T> && ranges_std::random_access_range<T>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

// TODO: investigate bug
TEST(MyTestSuite, take_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::take(t, 10);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::sized_range<T> && ranges_v3::random_access_range<T>);
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
#ifdef COUNT_ERROR
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
        }
    });
}

TEST(MyTestSuite, take_while_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::take_while(t, [](auto&&) { return true; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_HOLD(T, !ranges_std::common_range<V>);
            EXPECT_HOLD(T, !ranges_std::sized_range<V>);
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
            EXPECT_HOLD(T, !ranges_std::borrowed_range<V>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

// TODO: Investigate inconsistency
TEST(MyTestSuite, take_while_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::take_while(t, [](auto&&) { return true; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
#ifdef COUNT_ERROR
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::random_access_iterator_tag>);
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
            EXPECT_HOLD(T, !ranges_v3::common_range<V>);
            EXPECT_HOLD(T, !ranges_v3::sized_range<V>);
            EXPECT_HOLD(T, !ranges_v3::borrowed_range<V>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

// TODO: investigate bug
TEST(MyTestSuite, drop_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::drop(t, 10);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::common_range<T>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
#ifdef COUNT_ERROR
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
#endif
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

// TODO: investigate bug
TEST(MyTestSuite, drop_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::drop(t, 10);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_v3::common_range<V>, ranges_v3::common_range<T>);
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
#ifdef COUNT_ERROR
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
        }
    });
}

TEST(MyTestSuite, drop_while_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::drop_while(t, [](auto&&) { return true; });
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, range_category<T>);
            EXPECT_EQAL(T, ranges_std::common_range<V>, ranges_std::common_range<T>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::common_range<T> && ranges_std::random_access_range<T>);
            EXPECT_HOLD(T, !ranges_std::range<const V>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

TEST(MyTestSuite, common_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_std::common(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, std::conditional_t<
                ranges_std::common_range<T> || (ranges_std::sized_range<T> && ranges_std::random_access_range<T>),
                range_category<T>,
                clamp_down<range_category<T>, std::forward_iterator_tag>>);
            EXPECT_HOLD(T, ranges_std::common_range<V>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

// TODO: Investigate bug
TEST(MyTestSuite, common_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T>) {
            T t;
            auto v = views_v3::common(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
            EXPECT_SAME(T, range_category<V>, std::conditional_t<
                ranges_v3::common_range<T> || (ranges_v3::sized_range<T> && ranges_v3::random_access_range<T>),
                range_category<T>,
                clamp_down<range_category<T>, std::forward_iterator_tag>>);
            EXPECT_HOLD(T, ranges_v3::common_range<V>);
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
#ifdef COUNT_ERROR
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
        }
    });
}

// TODO: Investigate bug
TEST(MyTestSuite, reverse_std) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T> && ranges_std::bidirectional_range<T>) {
            T t;
            auto v = views_std::reverse(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_std::range_reference_t<V>, ranges_std::range_reference_t<T>);
            EXPECT_SAME(T, ranges_std::range_value_t<V>, ranges_std::range_value_t<T>);
#ifdef COUNT_ERROR
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::random_access_iterator_tag>);
            EXPECT_EQAL(T, ranges_std::range<const V>, ranges_std::range<const T>);
#endif
            EXPECT_HOLD(T, ranges_std::common_range<V>);
            EXPECT_EQAL(T, ranges_std::sized_range<V>, ranges_std::sized_range<T>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}

TEST(MyTestSuite, reverse_v3) {
    test_all([]<typename T>() {
        if constexpr (std::default_initializable<T> && std::is_copy_constructible_v<T> && ranges_v3::bidirectional_range<T>) {
            T t;
            auto v = views_v3::reverse(t);
            using V = decltype(v);
            EXPECT_SAME(T, ranges_v3::range_reference_t<V>, ranges_v3::range_reference_t<T>);
            EXPECT_SAME(T, ranges_v3::range_value_t<V>, ranges_v3::range_value_t<T>);
#ifdef COUNT_ERROR
            EXPECT_SAME(T, range_category<V>, clamp_down<range_category<T>, std::random_access_iterator_tag>);
            EXPECT_EQAL(T, ranges_v3::range<const V>, ranges_v3::range<const T>);
#endif
            EXPECT_HOLD(T, ranges_v3::common_range<V>);
            EXPECT_EQAL(T, ranges_v3::sized_range<V>, ranges_v3::sized_range<T>);
            EXPECT_EQAL(T, view_future::constant_range<V>, view_future::constant_range<T>);
        }
    });
}
