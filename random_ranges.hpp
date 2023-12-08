// This file is generated with seed = 12345

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
    std::map<int, zstring>,
    std::forward_list<decltype(ref_add_rref(std::declval<std::multimap<char, std::deque<zstring>>>()))>,
    std::multimap<std::byte, std::array<std::multimap<int, czstring>, 7>>,
    std::unordered_multimap<double, double>,
    std::multimap<signed char, decltype(ref_remove_all(std::declval<std::unordered_map<char, std::array<char, 3>>>()))>,
    std::array<double, 8>,
    std::set<std::span<std::span<decltype(ref_add_rref(std::declval<std::unordered_map<char, unsigned int>>())), 0>>>,
    std::multiset<std::array<decltype(std::views::iota(18)), 8>>,
    std::vector<decltype(val_remove_all(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::multimap<signed char, std::multiset<long>>>()))>()))>,
    decltype(val_remove_all(std::declval<std::unordered_map<long long, std::unordered_multimap<std::byte, decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::set<unsigned int>>()))>>>())),
    decltype(to_common(std::declval<std::set<std::deque<int>>>())),
    std::unordered_multimap<bool, std::unordered_multimap<bool, decltype(val_add_const(std::declval<std::list<int>>()))>>,
    std::multiset<std::array<long, 7>>,
    std::multimap<long, char>,
    std::deque<std::unordered_multimap<char, bool>>,
    std::list<float>,
    std::multimap<signed char, decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(ref_add_lref(std::declval<decltype(to_const_iterable(std::declval<std::array<decltype(to_uncommon(std::declval<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::span<std::unordered_multimap<double, decltype(std::views::empty<zstring>)>, 0>>()))>())), 6>>()))>()))>()))>,
    std::unordered_map<unsigned char, int>,
    std::unordered_multimap<unsigned int, std::forward_list<std::forward_list<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::multiset<int>>()))>>>,
    std::span<czstring, 0>,
    std::unordered_map<unsigned char, decltype(ref_add_volatile(std::declval<std::deque<std::string>>()))>,
    std::unordered_multimap<std::size_t, decltype(to_const_iterable(std::declval<std::forward_list<decltype(to_borrowed(std::declval<decltype(val_remove_all(std::declval<std::multimap<std::string, std::vector<float>>>()))>()))>>()))>,
    std::multimap<char, std::forward_list<std::array<std::string, 1>>>,
    std::multiset<decltype(val_add_const(std::declval<decltype(val_add_const(std::declval<std::set<signed char>>()))>()))>,
    decltype(to_unconst_iterable(std::declval<std::multiset<decltype(std::views::iota(34))>>())),
    decltype(to_unconst_iterable(std::declval<std::map<std::string, std::list<zstring>>>())),
    std::multiset<long long>,
    std::unordered_map<signed char, decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<decltype(to_unsized(std::declval<std::forward_list<decltype(ref_remove_all(std::declval<std::array<std::vector<double>, 8>>()))>>()))>()))>,
    std::unordered_map<std::string, std::forward_list<decltype(std::views::iota(19))>>,
    std::deque<long>,
    std::unordered_map<std::byte, decltype(val_add_const(std::declval<std::unordered_map<unsigned int, std::vector<double>>>()))>,
    std::multimap<std::size_t, std::span<long long>>,
    std::array<std::array<int, 3>, 9>,
    std::map<int, std::span<decltype(std::views::empty<int>)>>,
    std::span<decltype(std::declval<std::vector<std::size_t>>() | std::views::all)>,
    std::vector<std::string>,
    std::unordered_multimap<unsigned int, float>,
    std::span<unsigned int>,
    std::multimap<unsigned int, czstring>,
    std::set<decltype(std::declval<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<decltype(val_add_const(std::declval<std::span<std::byte, 0>>()))>()))>() | std::views::all)>,
    std::forward_list<std::array<std::forward_list<std::forward_list<decltype(std::views::iota(22))>>, 2>>,
    std::unordered_map<float, bool>,
    std::array<decltype(val_add_const(std::declval<std::unordered_map<signed char, decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::multimap<long, unsigned char>>()))>>())), 7>,
    std::map<unsigned int, decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::span<std::vector<decltype(val_add_const(std::declval<decltype(ref_add_volatile(std::declval<std::multiset<bool>>()))>()))>, 0>>()))>,
    std::vector<std::multimap<double, long>>,
    std::vector<decltype(to_unsized(std::declval<std::list<std::map<long long, decltype(ref_add_const(std::declval<decltype(to_constant(std::declval<std::deque<signed char>>()))>()))>>>()))>,
    decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(to_const_iterable(std::declval<std::unordered_map<bool, decltype(std::views::empty<float>)>>()))>())),
    decltype(val_remove_all(std::declval<decltype(ref_add_lref(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(to_common(std::declval<std::vector<std::unordered_map<std::size_t, double>>>()))>()))>()))>())),
    std::multimap<double, std::unordered_multimap<signed char, decltype(val_add_volatile(std::declval<std::multimap<unsigned char, std::size_t>>()))>>,
    std::map<long, decltype(to_constant(std::declval<std::map<unsigned int, std::array<unsigned char, 4>>>()))>,
    std::span<decltype(ref_add_lref(std::declval<std::unordered_multimap<std::string, std::set<bool>>>()))>,
    std::deque<decltype(ref_add_rref(std::declval<decltype(val_add_volatile(std::declval<decltype(to_unsized(std::declval<std::set<czstring>>()))>()))>()))>,
    std::deque<std::string>,
    decltype(to_unconst_iterable(std::declval<decltype(to_uncommon(std::declval<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::array<std::byte, 5>>()))>()))>())),
    std::set<std::multiset<std::unordered_map<bool, bool>>>,
    std::map<signed char, std::forward_list<std::vector<unsigned int>>>,
    decltype(ref_add_rref(std::declval<decltype(val_add_volatile(std::declval<std::span<signed char, 0>>()))>())),
    decltype(to_unsized(std::declval<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::array<unsigned char, 10>>()))>())),
    std::forward_list<decltype(std::views::iota(20))>,
    std::deque<std::multiset<decltype(ref_add_const(std::declval<std::span<std::unordered_multimap<unsigned int, float>>>()))>>,
    std::unordered_map<long long, std::map<unsigned char, unsigned char>>,
    std::vector<bool>,
    std::deque<std::size_t>,
    std::unordered_map<signed char, std::multiset<decltype(ref_add_volatile(std::declval<std::set<std::string>>()))>>,
    std::set<std::multimap<float, std::vector<unsigned int>>>,
    std::multimap<int, std::deque<unsigned int>>,
    std::list<long>,
    std::set<decltype(val_add_volatile(std::declval<decltype(to_const_iterable(std::declval<decltype(val_remove_all(std::declval<decltype(val_add_volatile(std::declval<std::list<signed char>>()))>()))>()))>()))>,
    std::list<decltype(val_remove_all(std::declval<decltype(to_unborrowed(std::declval<decltype(to_unborrowed(std::declval<decltype(ref_add_const(std::declval<std::set<decltype(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(to_constant(std::declval<std::forward_list<std::string>>()))>()))>() | std::views::all)>>()))>()))>()))>()))>,
    std::deque<std::vector<decltype(std::declval<std::unordered_map<double, decltype(std::views::empty<bool>)>>() | std::views::all)>>,
    std::unordered_map<std::size_t, std::multiset<std::deque<std::set<decltype(std::views::iota(22))>>>>,
    std::vector<std::unordered_map<unsigned int, decltype(std::views::empty<long long>)>>,
    std::vector<decltype(val_remove_all(std::declval<decltype(val_add_const(std::declval<decltype(val_remove_all(std::declval<decltype(ref_remove_all(std::declval<std::multiset<std::multimap<bool, decltype(to_borrowed(std::declval<std::multimap<std::string, unsigned int>>()))>>>()))>()))>()))>()))>,
    std::vector<std::span<decltype(to_unsized(std::declval<std::forward_list<unsigned char>>())), 0>>,
    std::array<std::vector<std::size_t>, 7>,
    std::forward_list<std::vector<decltype(std::declval<std::unordered_multimap<std::string, int>>() | std::views::all)>>,
    std::unordered_multimap<bool, zstring>,
    std::unordered_multimap<std::byte, decltype(to_borrowed(std::declval<std::set<std::list<char>>>()))>,
    std::unordered_multimap<long, std::map<int, decltype(ref_add_const(std::declval<std::span<long long>>()))>>,
    std::vector<std::unordered_multimap<std::string, std::deque<decltype(to_unsized(std::declval<std::multimap<std::string, int>>()))>>>,
    std::span<decltype(std::views::iota(63)), 0>,
    std::map<int, std::string>,
    std::span<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<decltype(to_unborrowed(std::declval<std::array<std::multiset<std::forward_list<long long>>, 3>>()))>()))>,
    std::vector<std::multimap<bool, std::unordered_multimap<std::byte, unsigned char>>>,
    std::vector<decltype(to_common(std::declval<std::unordered_map<bool, decltype(to_uncommon(std::declval<decltype(ref_remove_all(std::declval<std::span<zstring>>()))>()))>>()))>,
    std::unordered_map<char, std::multimap<unsigned int, signed char>>,
    std::span<std::set<bool>, 0>,
    decltype(to_unconst_iterable(std::declval<decltype(ref_add_rref(std::declval<std::multiset<decltype(ref_add_rref(std::declval<decltype(val_add_volatile(std::declval<decltype(val_add_const(std::declval<decltype(std::declval<std::unordered_map<unsigned char, unsigned char>>() | std::views::all)>()))>()))>()))>>()))>())),
    std::vector<std::forward_list<std::array<char, 5>>>,
    std::vector<std::span<std::size_t>>,
    std::array<int, 2>,
    std::set<decltype(to_sized(std::declval<std::vector<char>>()))>,
    std::unordered_map<long long, decltype(val_add_volatile(std::declval<std::map<unsigned char, decltype(std::views::empty<float>)>>()))>,
    std::unordered_map<char, decltype(std::views::empty<int>)>,
    std::unordered_map<std::byte, signed char>,
    decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::vector<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::multiset<decltype(val_remove_all(std::declval<std::map<long long, std::string>>()))>>()))>>())),
    decltype(val_add_const(std::declval<decltype(ref_add_const(std::declval<decltype(val_remove_all(std::declval<std::map<std::string, decltype(ref_add_const(std::declval<std::map<bool, long>>()))>>()))>()))>())),
    std::span<double>,
    std::vector<std::vector<std::string>>,
    std::deque<std::vector<std::array<decltype(val_remove_all(std::declval<decltype(to_common(std::declval<decltype(to_unsized(std::declval<std::unordered_multimap<unsigned char, decltype(std::views::empty<int>)>>()))>()))>())), 7>>>
>;
