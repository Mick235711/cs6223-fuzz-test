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
    std::map<int, std::string_view>,
    std::forward_list<decltype(to_unconst_iterable(std::declval<decltype(ref_add_rref(std::declval<std::multimap<std::string_view, std::deque<std::string_view>>>()))>()))>,
    std::multimap<std::byte, std::array<std::multimap<int, zstring>, 7>>,
    std::unordered_multimap<double, double>,
    std::multimap<signed char, decltype(ref_remove_all(std::declval<std::unordered_map<char, std::array<char, 3>>>()))>,
    std::array<double, 8>,
    std::set<std::span<std::span<decltype(ref_add_rref(std::declval<std::unordered_map<char, unsigned int>>())), 0>>>,
    std::multiset<std::array<czstring, 3>>,
    decltype(val_remove_all(std::declval<std::multimap<int, czstring>>())),
    std::forward_list<std::multimap<unsigned int, std::string_view>>,
    std::span<decltype(to_sized(std::declval<std::set<decltype(std::views::iota(42))>>()))>,
    decltype(to_common(std::declval<std::set<std::array<std::deque<std::byte>, 6>>>())),
    std::map<double, std::vector<decltype(val_add_const(std::declval<std::list<zstring>>()))>>,
    std::list<unsigned int>,
    std::multiset<std::vector<std::forward_list<std::list<std::string>>>>,
    std::list<decltype(ref_remove_all(std::declval<std::map<signed char, float>>()))>,
    std::deque<unsigned char>,
    std::multimap<std::string_view, std::map<double, long>>,
    std::multimap<bool, std::unordered_multimap<float, std::deque<std::string>>>,
    std::multimap<std::byte, std::multiset<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::list<int>>()))>>,
    std::deque<std::set<decltype(std::views::empty<std::byte>)>>,
    std::vector<decltype(to_unsized(std::declval<decltype(to_uncommon(std::declval<std::forward_list<decltype(to_unsized(std::declval<std::unordered_multimap<double, signed char>>()))>>()))>()))>,
    std::list<decltype(to_common(std::declval<std::forward_list<decltype(ref_add_rref(std::declval<decltype(ref_add_volatile(std::declval<std::deque<std::span<std::string_view, 0>>>()))>()))>>()))>,
    std::multimap<char, std::forward_list<std::array<std::string, 1>>>,
    std::multiset<decltype(val_add_const(std::declval<decltype(val_add_const(std::declval<std::set<signed char>>()))>()))>,
    decltype(to_unconst_iterable(std::declval<std::deque<czstring>>())),
    std::span<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::map<std::size_t, std::unordered_multimap<char, decltype(ref_remove_all(std::declval<decltype(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(ref_add_volatile(std::declval<std::forward_list<double>>()))>()))>() | std::views::all)>()))>>>())), 0>,
    std::vector<std::set<decltype(to_sized(std::declval<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<std::deque<decltype(to_uncommon(std::declval<decltype(val_add_const(std::declval<decltype(to_unborrowed(std::declval<std::set<std::string>>()))>()))>()))>>()))>()))>>,
    std::vector<char>,
    decltype(to_uncommon(std::declval<std::unordered_map<double, float>>())),
    std::unordered_multimap<bool, std::deque<std::span<unsigned char>>>,
    std::vector<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::deque<int>>()))>,
    std::list<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<decltype(ref_add_lref(std::declval<decltype(ref_add_const(std::declval<std::span<decltype(val_add_volatile(std::declval<std::forward_list<std::size_t>>()))>>()))>()))>()))>,
    std::multimap<signed char, std::unordered_multimap<unsigned char, std::multimap<unsigned int, decltype(std::views::iota(13))>>>,
    std::multimap<double, std::deque<std::vector<std::byte>>>,
    decltype(std::declval<std::multimap<unsigned char, decltype(ref_remove_all(std::declval<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<decltype(ref_add_rref(std::declval<std::span<double, 0>>()))>()))>()))>>() | std::views::all),
    std::set<unsigned char>,
    std::forward_list<std::forward_list<decltype(std::views::empty<long>)>>,
    std::unordered_map<float, int>,
    std::array<std::unordered_map<signed char, std::multimap<std::string_view, unsigned char>>, 7>,
    std::unordered_map<char, std::size_t>,
    std::deque<decltype(ref_add_volatile(std::declval<decltype(ref_add_rref(std::declval<std::multiset<std::multiset<decltype(ref_add_const(std::declval<std::map<std::byte, long>>()))>>>()))>()))>,
    std::list<long long>,
    std::multimap<signed char, std::string_view>,
    decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::unordered_map<std::string, std::array<std::array<std::byte, 5>, 8>>>())),
    decltype(ref_add_lref(std::declval<std::forward_list<std::string_view>>())),
    std::multiset<zstring>,
    std::map<unsigned char, std::set<std::array<std::map<std::size_t, double>, 6>>>,
    decltype(val_remove_all(std::declval<decltype(to_sized(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::map<unsigned char, std::string_view>>()))>()))>())),
    std::array<decltype(std::views::iota(93, 100)), 4>,
    std::vector<std::list<int>>,
    std::unordered_map<std::size_t, zstring>,
    std::deque<char>,
    std::multimap<std::byte, std::unordered_map<unsigned int, std::list<long>>>,
    std::vector<std::size_t>,
    std::forward_list<std::span<decltype(std::declval<std::unordered_multimap<bool, long long>>() | std::views::all)>>,
    std::span<std::unordered_multimap<int, char>, 0>,
    std::set<decltype(to_common(std::declval<std::list<decltype(to_borrowed(std::declval<decltype(ref_add_volatile(std::declval<std::set<std::unordered_map<char, signed char>>>()))>()))>>()))>,
    decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::span<decltype(to_constant(std::declval<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<decltype(to_constant(std::declval<std::unordered_multimap<float, std::forward_list<zstring>>>()))>()))>())), 0>>())),
    std::multiset<std::list<std::deque<decltype(to_uncommon(std::declval<std::multiset<std::byte>>()))>>>,
    std::deque<std::multiset<decltype(ref_add_const(std::declval<std::span<std::unordered_multimap<unsigned int, float>>>()))>>,
    std::unordered_map<long long, std::map<unsigned char, unsigned char>>,
    std::vector<bool>,
    std::deque<std::size_t>,
    std::unordered_map<signed char, std::multiset<decltype(ref_add_volatile(std::declval<std::set<std::string>>()))>>,
    std::unordered_map<std::string, decltype(std::views::empty<bool>)>,
    std::deque<char>,
    std::multimap<std::string, unsigned char>,
    std::array<std::list<std::multiset<std::forward_list<decltype(std::views::iota(29))>>>, 3>,
    std::array<decltype(ref_add_rref(std::declval<decltype(ref_add_const(std::declval<decltype(val_add_volatile(std::declval<std::array<std::multimap<int, std::size_t>, 7>>()))>()))>())), 7>,
    std::unordered_map<signed char, decltype(to_unborrowed(std::declval<decltype(ref_add_const(std::declval<decltype(std::declval<std::set<decltype(decay_to_lower_opt<std::forward_iterator_tag>(std::declval<std::vector<std::size_t>>()))>>() | std::views::all)>()))>()))>,
    std::array<std::set<decltype(decay_to_lower_opt<std::random_access_iterator_tag>(std::declval<std::deque<std::byte>>()))>, 7>,
    std::map<std::byte, decltype(to_unborrowed(std::declval<std::set<decltype(to_common(std::declval<std::multiset<long long>>()))>>()))>,
    std::set<std::array<zstring, 2>>,
    decltype(to_sized(std::declval<std::vector<double>>())),
    std::multiset<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<decltype(decay_to_lower<std::input_iterator_tag>(std::declval<std::map<signed char, std::list<decltype(ref_add_const(std::declval<decltype(to_constant(std::declval<decltype(ref_add_lref(std::declval<std::array<long long, 1>>()))>()))>()))>>>()))>()))>,
    std::multiset<int>,
    std::forward_list<std::string_view>,
    std::vector<std::string>,
    std::map<std::size_t, decltype(to_constant(std::declval<decltype(to_const_iterable(std::declval<std::forward_list<std::byte>>()))>()))>,
    std::vector<decltype(std::views::empty<std::byte>)>,
    std::span<float>,
    std::list<double>,
    std::array<std::map<long, std::set<unsigned int>>, 7>,
    std::list<long>,
    std::set<int>,
    std::multiset<decltype(to_const_iterable(std::declval<std::map<double, decltype(val_add_const(std::declval<std::unordered_map<std::string_view, std::unordered_map<std::size_t, int>>>()))>>()))>,
    std::span<decltype(decay_to_lower_opt<std::bidirectional_iterator_tag>(std::declval<decltype(to_unborrowed(std::declval<std::array<std::multiset<std::forward_list<long long>>, 3>>()))>()))>,
    std::vector<std::multimap<bool, std::unordered_multimap<std::byte, unsigned char>>>,
    std::vector<decltype(to_common(std::declval<std::unordered_map<bool, decltype(to_uncommon(std::declval<decltype(ref_remove_all(std::declval<std::span<std::string_view>>()))>()))>>()))>,
    std::unordered_map<char, std::multimap<unsigned int, signed char>>,
    std::span<std::set<bool>, 0>,
    decltype(to_unconst_iterable(std::declval<decltype(ref_add_rref(std::declval<std::multiset<decltype(ref_add_rref(std::declval<decltype(val_add_volatile(std::declval<decltype(val_add_const(std::declval<decltype(std::declval<std::unordered_map<unsigned char, unsigned char>>() | std::views::all)>()))>()))>()))>>()))>())),
    std::vector<std::forward_list<std::array<char, 5>>>,
    std::vector<std::span<std::size_t>>,
    std::array<int, 2>,
    std::set<decltype(to_sized(std::declval<std::vector<char>>()))>,
    std::unordered_map<char, decltype(val_add_volatile(std::declval<std::deque<decltype(std::views::iota(63, 79))>>()))>,
    std::list<int>,
    std::span<int, 0>
>;
