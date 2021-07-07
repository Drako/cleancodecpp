#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

template <char... Chars>
struct string {
    inline constexpr static char const value[] = { Chars..., '\0' };
};

namespace detail {
using std::uint32_t;
template <uint32_t Head, bool Done = (Head < 10), uint32_t... Tail>
struct to_string;

template <uint32_t Head, uint32_t... Tail>
struct to_string<Head, true, Tail...>
    : string<Head, Tail...> {
    using type = string<Head + '0', (Tail + '0')...>;
};

template <uint32_t Head, uint32_t... Tail>
struct to_string<Head, false, Tail...>
    : to_string<Head / 10u, ((Head / 10u) < 10), Head % 10u, Tail...> {
};

template <uint32_t Head>
using to_string_t = typename to_string<Head>::type;
}

template <std::uint32_t N>
struct to_string : detail::to_string<N> {
};

template <>
struct to_string<0u> {
    using type = string<'0'>;
};

template <char... CharsA, char... CharsB>
auto operator+(string<CharsA...>, string<CharsB...>) -> string<CharsA..., CharsB...>;

template <std::uint32_t N>
using to_string_t = typename to_string<N>::type;
template <std::uint32_t N>
static char const* const to_string_v = to_string_t<N>::value;

template <std::uint32_t N, bool F = (N % 3 == 0), bool B = (N % 5 == 0)>
struct fizzbuzz {
    using type = to_string_t<N>;
};
template <std::uint32_t N>
struct fizzbuzz<N, true, true> {
    using type = string<'F', 'i', 'z', 'z', 'B', 'u', 'z', 'z'>;
};
template <std::uint32_t N>
struct fizzbuzz<N, true, false> {
    using type = string<'F', 'i', 'z', 'z'>;
};
template <std::uint32_t N>
struct fizzbuzz<N, false, true> {
    using type = string<'B', 'u', 'z', 'z'>;
};
template <std::uint32_t N>
using fizzbuzz_t = typename fizzbuzz<N>::type;

template <typename Seq = std::make_integer_sequence<std::uint32_t, 100u>>
struct compile;
template <std::uint32_t... Idx>
struct compile<std::integer_sequence<std::uint32_t, Idx...>> {
    using type = decltype(((fizzbuzz_t<Idx + 1> {} + string<'\n'> {}) + ...));
};
using compile_t = typename compile<>::type;

// using the function from templates.cxx
std::string runtime_fizzbuzz(int n);

TEST(FizzBuzzTest, fizz_buzz_compile_time)
{
    std::string expected;
    for (int n = 0; n < 100; ++n) {
        expected += runtime_fizzbuzz(n + 1) + "\n";
    }

    std::string const actual = compile_t::value;
    EXPECT_EQ(expected, actual);
}
