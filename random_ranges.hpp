// This file is generated with seed = 11111

#include <ranges>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <span>
#include <string>
#include <cstddef>
#include <utility>

struct zsentinel {
    auto operator==(char* p) const -> bool {
        return *p == '\0';
    }
};

struct zstring {
    char* p;
    auto begin() const -> char* { return p; }
    auto end() const -> zsentinel { return {}; }
};

struct czsentinel {
    auto operator==(const char* p) const -> bool {
        return *p == '\0';
    }
};

struct czstring {
    const char* p;
    auto begin() const -> const char* { return p; }
    auto end() const -> czsentinel { return {}; }
};

template<typename...> struct typelist {};
using random_ranges = typelist<
    std::forward_list<double>,
    std::list<std::multimap<std::byte, std::remove_cvref_t<decltype(to_uncommon(std::declval<std::remove_cvref_t<decltype(ref_add_const(std::declval<std::remove_cvref_t<decltype(to_unsized(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::remove_cvref_t<decltype(to_sized(std::declval<std::multimap<signed char, std::size_t>>()))>>()))>>()))>>()))>>()))>>>,
    std::span<double, 0>,
    std::map<std::size_t, std::remove_cvref_t<decltype(to_uncommon(std::declval<std::deque<std::string>>()))>>,
    std::vector<std::remove_cvref_t<decltype(to_borrowed(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::deque<int>>()))>>()))>>,
    std::multimap<char, std::remove_cvref_t<decltype(std::declval<std::map<unsigned char, std::span<std::remove_cvref_t<decltype(val_add_const(std::declval<std::unordered_multimap<unsigned int, std::remove_cvref_t<decltype(std::views::empty<long>)>>>()))>>>>() | std::views::all)>>,
    std::array<std::map<long, std::list<std::remove_cvref_t<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::multimap<int, int>>()))>>>, 9>,
    std::unordered_map<int, std::list<std::deque<std::size_t>>>,
    std::multimap<unsigned int, std::forward_list<bool>>,
    std::list<long>,
    std::array<std::vector<std::unordered_multimap<signed char, int>>, 2>,
    std::deque<std::size_t>,
    std::array<std::remove_cvref_t<decltype(to_common(std::declval<std::forward_list<std::map<std::string, float>>>()))>, 4>,
    std::array<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::remove_cvref_t<decltype(to_sized(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::unordered_multimap<std::size_t, std::array<std::remove_cvref_t<decltype(std::views::iota(35))>, 2>>>()))>>()))>>()))>, 10>,
    std::span<std::deque<std::remove_cvref_t<decltype(to_sized(std::declval<std::remove_cvref_t<decltype(val_add_const(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::forward_list<std::string_view>>()))>>()))>>()))>>>,
    std::vector<double>,
    std::unordered_map<unsigned char, std::remove_cvref_t<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::multimap<long long, unsigned int>>()))>>,
    std::map<bool, std::remove_cvref_t<decltype(to_sized(std::declval<std::unordered_multimap<signed char, signed char>>()))>>,
    std::unordered_map<unsigned char, std::remove_cvref_t<decltype(std::views::iota(62))>>,
    std::unordered_multimap<char, long>,
    std::vector<std::remove_cvref_t<decltype(to_common(std::declval<std::unordered_map<std::byte, std::string_view>>()))>>,
    std::multimap<unsigned char, std::remove_cvref_t<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::remove_cvref_t<decltype(to_uncommon(std::declval<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::span<std::remove_cvref_t<decltype(std::views::iota(18))>, 0>>()))>>()))>>()))>>,
    std::remove_cvref_t<decltype(to_uncommon(std::declval<std::multimap<unsigned char, float>>()))>,
    std::map<signed char, std::unordered_map<std::string, std::map<std::string_view, std::unordered_multimap<double, unsigned int>>>>,
    std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::deque<std::unordered_map<std::byte, std::vector<double>>>>()))>,
    std::span<std::string_view>,
    std::span<std::remove_cvref_t<decltype(to_sized(std::declval<std::multimap<std::size_t, std::remove_cvref_t<decltype(std::declval<std::vector<std::remove_cvref_t<decltype(std::views::iota(60))>>>() | std::views::all)>>>()))>, 0>,
    std::forward_list<float>,
    std::unordered_map<double, std::string_view>,
    std::array<std::span<double, 0>, 5>,
    std::array<long, 9>,
    std::forward_list<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::map<std::string_view, std::span<std::deque<std::string_view>, 0>>>()))>>,
    std::array<long, 6>,
    std::forward_list<std::list<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::unordered_map<char, std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::list<std::remove_cvref_t<decltype(std::views::iota(58))>>>()))>>>()))>>>,
    std::list<std::array<std::remove_cvref_t<decltype(val_remove_all(std::declval<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::unordered_multimap<unsigned char, std::string>>()))>>()))>, 1>>,
    std::span<std::forward_list<std::remove_cvref_t<decltype(to_unsized(std::declval<std::vector<std::map<std::string, float>>>()))>>>,
    std::unordered_map<long, std::remove_cvref_t<decltype(to_uncommon(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::span<std::map<std::string_view, double>, 0>>()))>>()))>>,
    std::list<std::vector<bool>>,
    std::map<std::size_t, std::array<czstring, 2>>,
    std::multimap<std::size_t, float>,
    std::remove_cvref_t<decltype(ref_remove_all(std::declval<std::vector<std::vector<char>>>()))>,
    std::unordered_map<std::size_t, long>,
    std::multimap<float, std::unordered_map<unsigned int, unsigned int>>,
    std::span<std::span<std::map<std::size_t, long>, 0>>,
    std::unordered_multimap<std::string_view, czstring>,
    std::remove_cvref_t<decltype(to_unsized(std::declval<std::span<int, 0>>()))>,
    std::multimap<long, std::multimap<std::string_view, std::remove_cvref_t<decltype(val_remove_all(std::declval<std::array<std::remove_cvref_t<decltype(to_borrowed(std::declval<std::array<float, 7>>()))>, 2>>()))>>>,
    std::multimap<int, std::remove_cvref_t<decltype(to_common(std::declval<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::unordered_multimap<float, std::remove_cvref_t<decltype(to_common(std::declval<std::unordered_map<std::byte, std::remove_cvref_t<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::vector<unsigned char>>()))>>>()))>>>()))>>()))>>,
    std::vector<float>,
    std::map<bool, std::remove_cvref_t<decltype(val_add_const(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::remove_cvref_t<decltype(to_common(std::declval<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::deque<czstring>>()))>>()))>>()))>>()))>>,
    std::multimap<double, zstring>,
    std::remove_cvref_t<decltype(std::declval<std::map<int, char>>() | std::views::all)>,
    std::unordered_map<long long, std::remove_cvref_t<decltype(val_remove_all(std::declval<std::list<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::vector<std::unordered_multimap<int, signed char>>>()))>>()))>>>()))>>,
    std::unordered_map<int, std::remove_cvref_t<decltype(std::views::empty<unsigned int>)>>,
    std::list<std::unordered_map<std::byte, std::map<std::byte, unsigned int>>>,
    std::remove_cvref_t<decltype(to_sized(std::declval<std::array<char, 2>>()))>,
    std::list<czstring>,
    std::span<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::remove_cvref_t<decltype(val_remove_all(std::declval<std::span<std::unordered_multimap<bool, unsigned int>, 0>>()))>>()))>>,
    std::remove_cvref_t<decltype(val_remove_all(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::vector<std::map<int, std::span<std::remove_cvref_t<decltype(std::views::empty<double>)>, 0>>>>()))>>()))>,
    std::span<std::forward_list<std::list<std::remove_cvref_t<decltype(val_add_const(std::declval<std::remove_cvref_t<decltype(to_borrowed(std::declval<std::unordered_map<std::string, float>>()))>>()))>>>>,
    std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::remove_cvref_t<decltype(to_borrowed(std::declval<std::span<std::list<std::remove_cvref_t<decltype(ref_add_const(std::declval<std::unordered_multimap<double, std::string>>()))>>>>()))>>()))>,
    std::forward_list<std::remove_cvref_t<decltype(std::declval<std::unordered_map<int, std::size_t>>() | std::views::all)>>,
    std::forward_list<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::deque<std::remove_cvref_t<decltype(ref_add_const(std::declval<std::remove_cvref_t<decltype(to_sized(std::declval<std::deque<bool>>()))>>()))>>>()))>>,
    std::list<std::remove_cvref_t<decltype(to_uncommon(std::declval<std::span<float>>()))>>,
    std::forward_list<std::multimap<float, std::byte>>,
    std::remove_cvref_t<decltype(val_remove_all(std::declval<std::remove_cvref_t<decltype(val_remove_all(std::declval<std::remove_cvref_t<decltype(val_remove_all(std::declval<std::remove_cvref_t<decltype(val_add_const(std::declval<std::array<czstring, 7>>()))>>()))>>()))>>()))>,
    std::unordered_map<bool, unsigned char>,
    std::array<std::list<std::remove_cvref_t<decltype(std::declval<std::array<long long, 2>>() | std::views::all)>>, 5>,
    std::map<long, bool>,
    std::unordered_multimap<signed char, std::vector<std::deque<std::remove_cvref_t<decltype(to_common(std::declval<std::remove_cvref_t<decltype(to_borrowed(std::declval<std::vector<std::remove_cvref_t<decltype(std::views::empty<unsigned char>)>>>()))>>()))>>>>,
    std::remove_cvref_t<decltype(to_const_iterable(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::vector<std::remove_cvref_t<decltype(to_uncommon(std::declval<std::deque<int>>()))>>>()))>>()))>,
    std::unordered_map<signed char, zstring>,
    std::forward_list<std::array<signed char, 8>>,
    std::array<unsigned int, 7>,
    std::remove_cvref_t<decltype(to_const_iterable(std::declval<std::multimap<std::byte, bool>>()))>,
    std::multimap<bool, std::remove_cvref_t<decltype(ref_remove_all(std::declval<std::unordered_map<std::size_t, std::remove_cvref_t<decltype(std::views::empty<int>)>>>()))>>,
    std::list<long>,
    std::vector<std::array<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::deque<std::map<double, signed char>>>()))>, 4>>,
    std::array<std::map<std::string_view, double>, 10>,
    std::array<std::remove_cvref_t<decltype(to_constant(std::declval<std::array<std::remove_cvref_t<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::map<long long, std::string>>()))>, 2>>()))>, 9>,
    std::array<std::remove_cvref_t<decltype(to_sized(std::declval<std::remove_cvref_t<decltype(to_sized(std::declval<std::remove_cvref_t<decltype(to_uncommon(std::declval<std::remove_cvref_t<decltype(to_const_iterable(std::declval<std::span<zstring>>()))>>()))>>()))>>()))>, 8>,
    std::unordered_map<std::string_view, unsigned int>,
    std::multimap<float, std::list<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::unordered_multimap<std::string, double>>()))>>>,
    std::array<float, 1>,
    std::forward_list<int>,
    std::span<std::remove_cvref_t<decltype(ref_add_const(std::declval<std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::multimap<char, std::unordered_multimap<bool, std::remove_cvref_t<decltype(to_unsized(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::multimap<std::string, unsigned char>>()))>>()))>>>>()))>>()))>>,
    std::span<std::span<std::deque<bool>, 0>>,
    std::vector<std::remove_cvref_t<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::unordered_multimap<bool, std::remove_cvref_t<decltype(std::views::empty<bool>)>>>()))>>,
    std::forward_list<std::array<std::multimap<std::byte, char>, 7>>,
    std::remove_cvref_t<decltype(ref_remove_all(std::declval<std::list<std::remove_cvref_t<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::remove_cvref_t<decltype(val_remove_all(std::declval<std::unordered_multimap<signed char, std::byte>>()))>>()))>>>()))>,
    std::remove_cvref_t<decltype(to_sized(std::declval<std::remove_cvref_t<decltype(to_sized(std::declval<std::unordered_map<unsigned char, std::array<float, 6>>>()))>>()))>,
    std::forward_list<std::deque<std::byte>>,
    std::unordered_multimap<unsigned int, std::remove_cvref_t<decltype(val_add_const(std::declval<std::multimap<std::byte, std::array<czstring, 10>>>()))>>,
    std::remove_cvref_t<decltype(to_sized(std::declval<std::list<std::remove_cvref_t<decltype(to_uncommon(std::declval<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::map<std::byte, char>>()))>>()))>>()))>>>()))>,
    std::deque<unsigned char>,
    std::array<std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::span<std::remove_cvref_t<decltype(std::views::iota(53, 96))>, 0>>()))>, 6>,
    std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::span<std::size_t>>()))>,
    std::unordered_map<float, std::remove_cvref_t<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::span<std::map<std::size_t, std::span<float, 0>>>>()))>>,
    std::remove_cvref_t<decltype(to_common(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::remove_cvref_t<decltype(to_unconst_iterable(std::declval<std::remove_cvref_t<decltype(std::declval<std::remove_cvref_t<decltype(ref_add_const(std::declval<std::remove_cvref_t<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::unordered_multimap<std::string_view, std::remove_cvref_t<decltype(to_unborrowed(std::declval<std::multimap<long long, std::remove_cvref_t<decltype(val_remove_all(std::declval<std::multimap<long, unsigned char>>()))>>>()))>>>()))>>()))>>() | std::views::all)>>()))>>()))>>()))>,
    std::forward_list<long long>
>;
