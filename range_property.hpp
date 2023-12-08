#include <ranges>
#include <concepts>
#include <utility>
#include <type_traits>

// reference implementation for P2278R4
namespace view_future
{
    struct deleted_t { };
    
    template <typename F>
    struct delete_if {
        [[no_unique_address]] F f;
    
        constexpr delete_if(F f) : f(std::move(f)) { }
    
        template <typename... Args>
            requires std::invocable<F const&, Args...>
        constexpr auto operator()(Args&&...) const -> deleted_t;
    };
    
    #define FWD(x) static_cast<decltype(x)&&>(x)
    #define RETURNS(e) -> decltype(e) { return e; }
    
    template <typename... Fs>
    class first_of
    { };
    
    template <typename... Fs>
    first_of(Fs...) -> first_of<Fs...>;
    
    template <typename F, typename... Fs>
    class first_of<F, Fs...>
    {
    private:
        using Rest = first_of<Fs...>;
        [[no_unique_address]] F first;
        [[no_unique_address]] Rest rest;
    
    public:
        constexpr first_of(F f, Fs... fs)
            : first(std::move(f))
            , rest(std::move(fs)...)
        { }
    
        template <typename... Args,
            bool First = std::is_invocable_v<F const&, Args...>,
            typename Which = std::conditional_t<First, F, Rest> const&>
        constexpr auto operator()(Args&&... args) const
            noexcept(std::is_nothrow_invocable_v<Which, Args...>)
            -> std::invoke_result_t<Which, Args...>
        {
            if constexpr (First) {
                return std::invoke(first, FWD(args)...);
            } else {
                return std::invoke(rest, FWD(args)...);
            }
        }
    
        template <typename... Args>
            requires std::invocable<F const&, Args...> &&
                std::same_as<
                    std::invoke_result_t<F const&, Args...>,
                    deleted_t>
        void operator()(Args&&...) const = delete;
    };
    ////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // const-iterator wrapping, pulled out of a views::const implementation https://godbolt.org/z/7MGEEj
    
    template <typename It> struct iterator_concept_for { };
    template <typename It> requires std::contiguous_iterator<It>
    struct iterator_concept_for<It> {
        using iterator_concept = std::contiguous_iterator_tag;
    };
    
    template <typename It> struct iterator_category_for { };
    template <std::forward_iterator It>
    struct iterator_category_for<It> {
        using iterator_category = typename std::iterator_traits<It>::iterator_category;
    };
    
    template <std::input_iterator It>
    using const_ref_for = std::common_reference_t<std::iter_value_t<It> const &&, std::iter_reference_t<It>>;
    
    template <typename It>
    concept ConstantIterator = std::input_iterator<It>
                            && std::same_as<const_ref_for<It>, std::iter_reference_t<It>>;
    
    template <typename R>
    concept ConstantRange = std::ranges::range<R> && ConstantIterator<std::ranges::iterator_t<R>>;
    
    template <typename T, typename U>
    concept DifferentFrom = not std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
    
    template <typename T, template <class...> class Z>
    inline constexpr bool is_specialization_of_v = false;
    template <class... Args, template <class...> class Z>
    inline constexpr bool is_specialization_of_v<Z<Args...>, Z> = true;
    
    template <typename T, template <class...> class Z>
    concept NotA = (not is_specialization_of_v<T, Z>);
    
    template <std::input_iterator It>
    class basic_const_iterator : public iterator_concept_for<It>
                               , public iterator_category_for<It>
    {
        It it;
    
    public:
        using value_type = std::iter_value_t<It>;
        using difference_type = std::iter_difference_t<It>;
        using reference = const_ref_for<It>;
    
        basic_const_iterator() = default;
        basic_const_iterator(It it) : it(std::move(it)) { }
        template <std::convertible_to<It> U>
        basic_const_iterator(basic_const_iterator<U> c) : it(std::move(c.base())) { }
        basic_const_iterator(std::convertible_to<It> auto&& c) : it(FWD(c)) { }
    
        auto operator++() -> basic_const_iterator& { ++it; return *this; }
        auto operator++(int) -> basic_const_iterator requires std::forward_iterator<It> { auto cpy = *this; ++*this; return cpy; }
        void operator++(int) { ++*this; }
    
        auto operator--() -> basic_const_iterator& requires std::bidirectional_iterator<It> { --it; return *this; }
        auto operator--(int) -> basic_const_iterator requires std::bidirectional_iterator<It> { auto cpy = *this; --*this; return cpy; }
    
        auto operator+(difference_type n) const -> basic_const_iterator requires std::random_access_iterator<It> { return const_iterator(it + n); }
        auto operator-(difference_type n) const -> basic_const_iterator requires std::random_access_iterator<It> { return const_iterator(it - n); }
        friend auto operator+(difference_type n, basic_const_iterator const& rhs) -> basic_const_iterator { return rhs + n; }
        auto operator+=(difference_type n) -> basic_const_iterator& requires std::random_access_iterator<It> { it += n; return *this; }
        auto operator-=(difference_type n) -> basic_const_iterator& requires std::random_access_iterator<It> { it -= n; return *this; }
        auto operator-(basic_const_iterator const& rhs) const -> difference_type requires std::random_access_iterator<It> { return it - rhs.it; }
        auto operator[](difference_type n) const -> reference requires std::random_access_iterator<It> { return it[n]; }
    
        auto operator*() const -> reference { return *it; }
        auto operator->() const -> value_type const* requires std::contiguous_iterator<It> { return std::to_address(it); }
    
        template <std::sentinel_for<It> S>
        auto operator==(S const& s) const -> bool {
            return it == s;
        }
    
        friend constexpr bool operator<(const basic_const_iterator& x, const basic_const_iterator& y)
          requires std::random_access_iterator<It>
        {
            return x.it < y.it;
        }
        friend constexpr bool operator>(const basic_const_iterator& x, const basic_const_iterator& y)
          requires std::random_access_iterator<It>
        {
            return x.it > y.it;
        }
        friend constexpr bool operator<=(const basic_const_iterator& x, const basic_const_iterator& y)
          requires std::random_access_iterator<It>
        {
            return x.it <= y.it;
        }
        friend constexpr bool operator>=(const basic_const_iterator& x, const basic_const_iterator& y)
          requires std::random_access_iterator<It>
        {
            return x.it >= y.it;
        }
        friend constexpr auto operator<=>(const basic_const_iterator& x, const basic_const_iterator& y)
          requires std::random_access_iterator<It> && std::three_way_comparable<It>
        {
            return x.it <=> y.it;
        }
    
        #ifdef USE_SPACESHIP
        template <DifferentFrom<basic_const_iterator> Rhs>
            requires std::random_access_iterator<It>
                 and std::totally_ordered_with<It, Rhs>
        auto operator<=>(Rhs const& rhs) const {
            if constexpr (std::three_way_comparable_with<It, Rhs>) {
                return it <=> rhs;
            } else if constexpr (std::sized_sentinel_for<Rhs, It>) {
                return (it - rhs) <=> 0;
            } else {
                if (it < rhs) return std::strong_ordering::less;
                if (rhs < it) return std::strong_ordering::greater;
                return std::strong_ordering::equal;
            }
        }
        #else
    
        #define REL_CMP(op)                                                                \
        template <DifferentFrom<basic_const_iterator> I>                                          \
          friend constexpr bool operator op(const basic_const_iterator& x, const I& y)     \
            requires std::random_access_iterator<It> && std::totally_ordered_with<It, I>   \
        {                                                                                  \
            return x.it op y;                                                              \
        }                                                                                  \
        template <NotA<basic_const_iterator> I>                                          \
          friend constexpr bool operator op(const I& x, const basic_const_iterator& y)     \
            requires std::random_access_iterator<It> && std::totally_ordered_with<It, I>   \
        {                                                                                  \
            return x op y.it;                                                              \
        }
    
        REL_CMP(<)
        REL_CMP(>)
        REL_CMP(<=)
        REL_CMP(>=)
    
        template <DifferentFrom<basic_const_iterator> I>
          friend constexpr auto operator<=>(const basic_const_iterator& x, const I& y)
            requires std::random_access_iterator<It>
                  && std::totally_ordered_with<It, I>
                  && std::three_way_comparable_with<It, I>
        {
            return x.it <=> y;
        }
        #endif
    
        template <std::sized_sentinel_for<It> S>
        auto operator-(S const& s) const -> std::iter_difference_t<It> {
            return it - s;
        }
    
        template <DifferentFrom<basic_const_iterator> S>
            requires std::sized_sentinel_for<S, It>
        friend auto operator-(S const& s, basic_const_iterator const& rhs) -> std::iter_difference_t<It> {
            return s - rhs.it;
        }
    
        auto base() -> It& { return it; }
        auto base() const -> It const& { return it; }
    };
    
}
    template <typename T, std::common_with<T> U>
    struct std::common_type<view_future::basic_const_iterator<T>, U> {
        using type = view_future::basic_const_iterator<std::common_type_t<T, U>>;
    };
    template <typename T, std::common_with<T> U>
    struct std::common_type<U, view_future::basic_const_iterator<T>> {
        using type = view_future::basic_const_iterator<std::common_type_t<T, U>>;
    };
    template <typename T, std::common_with<T> U>
    struct std::common_type<view_future::basic_const_iterator<T>, view_future::basic_const_iterator<U>> {
        using type = view_future::basic_const_iterator<std::common_type_t<T, U>>;
    };
namespace view_future {
    
    template <std::input_iterator It>
    constexpr auto make_const_iterator(It it) -> ConstantIterator auto {
        if constexpr (ConstantIterator<It>) {
            return it;
        } else {
            return basic_const_iterator<It>(it);
        }
    }
    
    template <std::input_iterator It>
    using const_iterator = decltype(make_const_iterator(std::declval<It>()));
    
    template <typename S>
    constexpr auto make_const_sentinel(S s) {
        if constexpr (std::input_iterator<S>) {
            return make_const_iterator(std::move(s));
        } else {
            return s;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    inline constexpr auto delete_if_nonborrowed_rvalue =
        delete_if([]<class R>(R&&)
            requires (not std::ranges::enable_borrowed_range<std::remove_cvref_t<R>>)
                  && std::is_rvalue_reference_v<R&&>
            { });
    
    inline constexpr auto possibly_const = []<std::ranges::range R>(R& r) -> auto& {
        if constexpr (ConstantRange<R const> and not ConstantRange<R>) {
            return const_cast<R const&>(r);
        } else {
            return r;
        }
    };
    
    inline constexpr auto cbegin = first_of(
        // 1. non-borrowed rvalue
        delete_if_nonborrowed_rvalue,
        // 2. possibly-wrapped begin of possibly-const r
        [](std::ranges::range auto&& r)
            RETURNS(make_const_iterator(std::ranges::begin(possibly_const(r))))
    );
    
    inline constexpr auto cend = first_of(
        // 1. non-borrowed rvalue
        delete_if_nonborrowed_rvalue,
        // 2. possibly-wrapped end of possibly-const r
        [](std::ranges::range auto&& r)
            RETURNS(make_const_sentinel(std::ranges::end(possibly_const(r))))
    );
    inline constexpr auto crbegin = first_of(
        // 1. non-borrowed rvalue
        delete_if_nonborrowed_rvalue,
        // 2. make_const_iterator(rbegin(E))
        [](std::ranges::range auto&& r) RETURNS(make_const_iterator(std::ranges::rbegin(possibly_const(r))))
    );
    inline constexpr auto crend = first_of(
        // 1. non-borrowed rvalue
        delete_if_nonborrowed_rvalue,
        // 2. make_const_iterator(rend(E))
        [](std::ranges::range auto&& r) RETURNS(make_const_iterator(std::ranges::rend(possibly_const(r))))
    );
    
    //////////////////////////
    // views::const_
    template <typename R>
    concept SimpleView = std::ranges::__simple_view<R>;
    
    template <std::ranges::input_range V>
        requires std::ranges::view<V>
    class const_view : public std::ranges::view_interface<const_view<V>> {
        V base = V();
    public:
        constexpr const_view() = default;
        constexpr const_view(V base) : base(std::move(base)) { }
    
        constexpr auto begin() requires (!SimpleView<V>) { return cbegin(base); }
        constexpr auto end() requires (!SimpleView<V>) { return cend(base); }
        constexpr auto size() requires std::ranges::sized_range<V> { return std::ranges::size(base); }
    
        constexpr auto begin() const requires std::ranges::range<V const> { return cbegin(base); }
        constexpr auto end() const requires std::ranges::range<V const> { return cend(base); }
        constexpr auto size() const requires std::ranges::sized_range<V const> { return std::ranges::size(base); }
    };
    
    
}
    template <typename V>
    inline constexpr bool ::std::ranges::enable_borrowed_range<view_future::const_view<V>> =
        std::ranges::enable_borrowed_range<V>;
namespace view_future {
    
    // libstdc++ specific (hopefully standard version coming soon!)
    inline constexpr auto const_ =
        []<std::ranges::viewable_range R>(R&& r)
        {
            using U = std::remove_cvref_t<R>;
    
            if constexpr (ConstantRange<std::views::all_t<R>>) {
                return std::views::all(FWD(r));
            } else if constexpr (ConstantRange<U const> and not std::ranges::view<U>) {
                return std::views::all(std::as_const(r));
            } else {
                return const_view<std::views::all_t<R>>(std::views::all(FWD(r)));
            }
        };

    template <std::indirectly_readable It>
    using iter_const_reference_t = std::common_reference_t<const std::iter_value_t<It>&&, std::iter_reference_t<It>>;

    template <class It>
    concept _constant_iterator =
        std::input_iterator<It> &&
        std::same_as<iter_const_reference_t<It>, std::iter_reference_t<It>>;

    template<class T>
    concept constant_range =
        std::ranges::input_range<T> &&
        _constant_iterator<std::ranges::iterator_t<T>>;
#undef FWD
#undef RETURNS
#undef REL_CMP
}

namespace ranges = std::ranges;
namespace views = std::views;
#define FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

template<std::input_or_output_iterator I>
using iter_trait = std::_ITER_TRAITS<I>;

template<std::input_or_output_iterator I>
using iter_category = std::_ITER_CONCEPT<I>;

// decay a range to arbitrary lower category
template<std::input_or_output_iterator It, typename lower_category>
requires std::derived_from<iter_category<It>, lower_category>
class decay_to_iterator
{
public:
    using iterator_type = It;
    using iterator_concept = lower_category;
    using iterator_category = lower_category;
    using value_type = std::iter_value_t<It>;
    using difference_type = std::iter_difference_t<It>;
    using reference = std::iter_reference_t<It>;

    constexpr decay_to_iterator() = default;
    constexpr explicit decay_to_iterator(It it) : current{std::move(it)} {}
    constexpr const It& base() const & noexcept { return current; }
    constexpr It base() && { return std::move(current); }
    constexpr reference operator*() const { return *current; }

    constexpr decay_to_iterator& operator++() { ++current; return *this; }
    constexpr decay_to_iterator operator++(int) { decay_to_iterator tmp = *this; ++current; return tmp; }
    constexpr decay_to_iterator& operator--() { --current; return *this; }
    constexpr decay_to_iterator operator--(int) { decay_to_iterator tmp = *this; --current; return tmp; }

    constexpr decay_to_iterator operator+(difference_type d) const
    { return decay_to_iterator{current + d}; }
    constexpr decay_to_iterator& operator+=(difference_type d)
    { current += d; return *this; }
    constexpr decay_to_iterator operator-(difference_type d) const
    { return decay_to_iterator{current - d}; }
    constexpr decay_to_iterator& operator-=(difference_type d)
    { current -= d; return *this; }
    constexpr reference operator[](difference_type d) const { return current[d]; }

    template<std::sentinel_for<It> S>
    friend bool operator==(const decay_to_iterator& x, const S& y)
    { return x.base() == y; }
    template<std::sized_sentinel_for<It> S>
    friend constexpr std::iter_difference_t<It>
    operator-(const decay_to_iterator& x, const S& y)
    { return x.base() - y; }
    template<std::sized_sentinel_for<It> S>
    friend constexpr std::iter_difference_t<It>
    operator-(const S& x, const decay_to_iterator& y)
    { return x - y.base(); }

private:
    It current{};
};

template<std::input_or_output_iterator It, typename lower_category>
class std::iterator_traits<decay_to_iterator<It, lower_category>>
{
public:
    using iterator_concept = lower_category;
    using iterator_category = lower_category;
    using value_type = std::iter_value_t<It>;
    using difference_type = std::iter_difference_t<It>;
    using reference = std::iter_reference_t<It>;
};

template<std::input_or_output_iterator It1, typename lower_category1, std::three_way_comparable_with<It1> It2, typename lower_category2>
constexpr std::compare_three_way_result_t<It1, It2>
operator<=>(const decay_to_iterator<It1, lower_category1>& x, const decay_to_iterator<It2, lower_category2>& y)
{ return x.base() <=> y.base(); }
template<std::input_or_output_iterator It1, typename lower_category1, std::input_or_output_iterator It2, typename lower_category2>
constexpr auto operator-(const decay_to_iterator<It1, lower_category1>& x, const decay_to_iterator<It2, lower_category2>& y) -> decltype(x.base() - y.base())
{ return x.base() - y.base(); }
template<std::input_or_output_iterator It2, typename lower_category2>
constexpr decay_to_iterator<It2, lower_category2>
operator+(std::iter_difference_t<It2> n, const decay_to_iterator<It2, lower_category2>& x)
{ return x + n; }

template<ranges::range R, typename lower_category>
requires std::derived_from<iter_category<ranges::iterator_t<R>>, lower_category>
class decay_to_view : public ranges::view_interface<decay_to_view<R, lower_category>>
{
private:
    R r_ = R();
    using underlying_t = decay_to_iterator<ranges::iterator_t<R>, lower_category>;

public:
    decay_to_view() requires std::default_initializable<R> = default;
    constexpr explicit decay_to_view(R base) : r_{std::move(base)} {}

    constexpr R base() const & requires std::copy_constructible<R> { return r_; }
    constexpr R base() && { return std::move(r_); }

    constexpr auto begin() { return underlying_t(ranges::begin(r_)); }
    constexpr auto begin() const requires ranges::range<const R> { return underlying_t(ranges::begin(r_)); }

    constexpr auto end()
    {
        if constexpr (ranges::common_range<R>) {
            return underlying_t(ranges::end(r_));
        } else {
            return ranges::end(r_);
        }
    }

    constexpr auto end() const requires ranges::range<const R>
    {
        if constexpr (ranges::common_range<const R>) {
            return underlying_t(ranges::end(r_));
        } else {
            return ranges::end(r_);
        }
    }

    constexpr auto size() requires ranges::sized_range<R> { return ranges::size(r_); }
    constexpr auto size() const requires ranges::sized_range<const R> { return ranges::size(r_); }
};

template<ranges::range R, typename lower_category>
inline constexpr bool ranges::enable_borrowed_range<decay_to_view<R, lower_category>> = ranges::enable_borrowed_range<R>;

// custom sentinel that is simply a wrapper
template<std::semiregular S>
class custom_sentinel_t
{
public:
    constexpr custom_sentinel_t() = default;
    constexpr explicit custom_sentinel_t(S s) : last{std::move(s)} {}
    template<typename S2> requires std::convertible_to<const S2&, S>
    constexpr custom_sentinel_t(const custom_sentinel_t<S2>& s) : last{s.last} {}
    template<typename S2> requires std::assignable_from<S&, const S2&>
    constexpr custom_sentinel_t& operator=(const custom_sentinel_t<S2>& s) { last = s.last; return *this;}

    constexpr S base() const { return last; }

private:
    S last{};
};

// wrap a range with a certain value_type/reference
template<std::input_or_output_iterator It, typename NewValueType = std::iter_value_t<It>, typename NewReference = std::iter_reference_t<It>>
class convert_to_iterator
{
public:
    using iterator_type = It;
    using iterator_concept = iter_category<It>;
    using iterator_category = iter_trait<It>::iterator_category;
    using value_type = NewValueType;
    using difference_type = std::iter_difference_t<It>;
    using reference = NewReference;

    constexpr convert_to_iterator() = default;
    constexpr explicit convert_to_iterator(It it) : current{std::move(it)} {}
    constexpr const It& base() const & noexcept { return current; }
    constexpr It base() && { return std::move(current); }
    constexpr reference operator*() const { return NewReference{*current}; }

    constexpr convert_to_iterator& operator++() { ++current; return *this; }
    constexpr convert_to_iterator operator++(int) { convert_to_iterator tmp = *this; ++current; return tmp; }
    constexpr convert_to_iterator& operator--() { --current; return *this; }
    constexpr convert_to_iterator operator--(int) { convert_to_iterator tmp = *this; --current; return tmp; }

    constexpr convert_to_iterator operator+(difference_type d) const
    { return convert_to_iterator{current + d}; }
    constexpr convert_to_iterator& operator+=(difference_type d)
    { current += d; return *this; }
    constexpr convert_to_iterator operator-(difference_type d) const
    { return convert_to_iterator{current - d}; }
    constexpr convert_to_iterator& operator-=(difference_type d)
    { current -= d; return *this; }
    constexpr reference operator[](difference_type d) const { return current[d]; }

    template<std::sentinel_for<It> S>
    friend bool operator==(const convert_to_iterator& x, const S& y)
    { return x.base() == y; }
    template<std::sized_sentinel_for<It> S>
    friend constexpr std::iter_difference_t<It>
    operator-(const convert_to_iterator& x, const S& y)
    { return x.base() - y; }
    template<std::sized_sentinel_for<It> S>
    friend constexpr std::iter_difference_t<It>
    operator-(const S& x, const convert_to_iterator& y)
    { return x - y.base(); }

    // support custom_sentinel
    template<std::semiregular S>
    friend bool operator==(const convert_to_iterator& x, const custom_sentinel_t<S>& y)
    { return x.base() == y.base(); }
    template<std::semiregular S>
    friend constexpr std::iter_difference_t<It>
    operator-(const convert_to_iterator& x, const custom_sentinel_t<S>& y)
    { return x.base() - y.base(); }
    template<std::semiregular S>
    friend constexpr std::iter_difference_t<It>
    operator-(const custom_sentinel_t<S>& x, const convert_to_iterator& y)
    { return x.base() - y.base(); }

private:
    It current{};
};

template<std::input_or_output_iterator It, typename NewValueType, typename NewReference>
class std::iterator_traits<convert_to_iterator<It, NewValueType, NewReference>>
{
public:
    using iterator_concept = iter_category<It>;
    using iterator_category = iter_trait<It>::iterator_category;
    using value_type = NewValueType;
    using difference_type = std::iter_difference_t<It>;
    using reference = NewReference;
};

template<std::input_or_output_iterator It1, typename V1, typename R1, std::three_way_comparable_with<It1> It2, typename V2, typename R2>
constexpr std::compare_three_way_result_t<It1, It2>
operator<=>(const convert_to_iterator<It1, V1, R1>& x, const convert_to_iterator<It2, V2, R2>& y)
{ return x.base() <=> y.base(); }
template<std::input_or_output_iterator It1, typename V1, typename R1, std::input_or_output_iterator It2, typename V2, typename R2>
constexpr auto operator-(const convert_to_iterator<It1, V1, R1>& x, const convert_to_iterator<It2, V2, R2>& y) -> decltype(x.base() - y.base())
{ return x.base() - y.base(); }
template<std::input_or_output_iterator It2, typename V2, typename R2>
constexpr convert_to_iterator<It2, V2, R2>
operator+(std::iter_difference_t<It2> n, const convert_to_iterator<It2, V2, R2>& x)
{ return x + n; }

enum class property { ForceDisable, Passive, ForceEnable };

template<ranges::range R, typename NewValueType = ranges::range_value_t<R>, typename NewReference = ranges::range_reference_t<R>,
         property EnableSize = property::Passive, property EnableConstIterable = property::Passive, property EnableBorrowed = property::Passive>
class convert_to_view : public ranges::view_interface<convert_to_view<R, NewValueType, NewReference>>
{
private:
    mutable R r_ = R();
    using underlying_t = convert_to_iterator<ranges::iterator_t<R>, NewValueType, NewReference>;

public:
    convert_to_view() requires std::default_initializable<R> = default;
    constexpr explicit convert_to_view(R base) : r_{std::move(base)} {}

    constexpr R base() const & requires std::copy_constructible<R> { return r_; }
    constexpr R base() && { return std::move(r_); }

    constexpr auto begin() requires (EnableConstIterable != property::ForceEnable) { return underlying_t(ranges::begin(r_)); }
    constexpr auto begin() const requires ((ranges::range<const R> && (EnableConstIterable != property::ForceDisable)) || (EnableConstIterable == property::ForceEnable))
    { return underlying_t(ranges::begin(r_)); }

    constexpr auto end() requires (EnableConstIterable != property::ForceEnable)
    {
        if constexpr (ranges::common_range<R>) {
            return underlying_t(ranges::end(r_));
        } else {
            return ranges::end(r_);
        }
    }

    constexpr auto end() const requires ((ranges::range<const R> && (EnableConstIterable != property::ForceDisable)) || (EnableConstIterable == property::ForceEnable))
    {
        if constexpr (ranges::common_range<const R>) {
            return underlying_t(ranges::end(r_));
        } else {
            return ranges::end(r_);
        }
    }

    constexpr auto size() requires (ranges::sized_range<R> && (EnableSize == property::Passive)) { return ranges::size(r_); }
    constexpr auto size() const requires (ranges::sized_range<const R> && (EnableSize == property::Passive)) { return ranges::size(r_); }
    constexpr auto size() const requires (EnableSize == property::ForceEnable) { return ranges::distance(r_); }
};

template<ranges::range R, typename NewValueType, typename NewReference, property EnableSize, property EnableConstIterable, property EnableBorrowed>
inline constexpr bool ranges::enable_borrowed_range<convert_to_view<R, NewValueType, NewReference, EnableSize, EnableConstIterable, EnableBorrowed>> =
    EnableBorrowed == property::Passive ? ranges::enable_borrowed_range<R> : (EnableBorrowed == property::ForceEnable);

template<typename T>
using add_deep_const_t = std::conditional_t<
    std::is_lvalue_reference_v<T>, const std::remove_reference_t<T>&,
    std::conditional_t<
        std::is_rvalue_reference_v<T>, const std::remove_reference_t<T>&&,
        std::add_const_t<T>
    >
>;
template<typename T>
using add_deep_volatile_t = std::conditional_t<
    std::is_lvalue_reference_v<T>, volatile std::remove_reference_t<T>&,
    std::conditional_t<
        std::is_rvalue_reference_v<T>, volatile std::remove_reference_t<T>&&,
        std::add_volatile_t<T>
    >
>;

// reference
// manipulation: remove all qualifier, +const, +volatile, +&, +&&
decltype(auto) ref_remove_all(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, std::remove_cvref_t<ranges::range_reference_t<Range>>>(FWD(R));
}
decltype(auto) ref_add_const(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, add_deep_const_t<ranges::range_reference_t<Range>>>(FWD(R));
}
decltype(auto) ref_add_volatile(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, add_deep_volatile_t<ranges::range_reference_t<Range>>>(FWD(R));
}
decltype(auto) ref_add_lref(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, std::add_lvalue_reference_t<ranges::range_reference_t<Range>>>(FWD(R));
}
decltype(auto) ref_add_rref(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, std::add_rvalue_reference_t<std::remove_reference_t<ranges::range_reference_t<Range>>>>(FWD(R));
}

// value type
// manipulation same as reference
decltype(auto) val_remove_all(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, std::remove_cvref_t<ranges::range_value_t<Range>>>(FWD(R));
}
decltype(auto) val_add_const(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, add_deep_const_t<ranges::range_value_t<Range>>>(FWD(R));
}
decltype(auto) val_add_volatile(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, add_deep_volatile_t<ranges::range_value_t<Range>>>(FWD(R));
}
decltype(auto) val_add_lref(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, std::add_lvalue_reference_t<ranges::range_value_t<Range>>>(FWD(R));
}
decltype(auto) val_add_rref(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, std::add_rvalue_reference_t<ranges::range_value_t<Range>>>(FWD(R));
}

// category
template<typename lower_category>
decltype(auto) decay_to_lower(ranges::input_range auto&& R)
{
    return decay_to_view<std::decay_t<decltype(R)>, lower_category>(FWD(R));
}

// common
decltype(auto) to_uncommon(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    auto V = convert_to_view<Range>(FWD(R));
    return ranges::subrange{V.begin(), custom_sentinel_t{V.end()}};
}
decltype(auto) to_common(ranges::range auto&& R)
{ return views::common(FWD(R)); }

// sized
decltype(auto) to_unsized(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::ForceDisable>(FWD(R));
}
decltype(auto) to_sized(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::ForceEnable>(FWD(R));
}

// const-iterable
decltype(auto) to_unconst_iterable(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::Passive, property::ForceDisable>(FWD(R));
}
decltype(auto) to_const_iterable(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::Passive, property::ForceEnable>(FWD(R));
}

// borrowed
decltype(auto) to_unborrowed(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::Passive, property::Passive, property::ForceDisable>(FWD(R));
}
decltype(auto) to_borrowed(ranges::range auto&& R)
{
    using Range = std::decay_t<decltype(R)>;
    return convert_to_view<Range, ranges::range_value_t<Range>, ranges::range_reference_t<Range>, property::Passive, property::Passive, property::ForceEnable>(FWD(R));
}

// constant
decltype(auto) to_constant(ranges::range auto&& R)
{ return view_future::const_(FWD(R)); }

// cannot force non-constant (UB)
