#include <gtest/gtest.h>

#include <string>
#include <utility>

namespace workshop {
template <char... Characters>
struct string {
    constexpr static char const value[] = { Characters..., '\0' };
};

template <int N>
struct fizzbuzz {
    using type = string<>;
};

template <int N>
using fizzbuzz_t = typename fizzbuzz<N>::type;
}

std::string runtime_fizzbuzz(int n)
{
    /*
    std::string result = std::string { n % 3 == 0 ? "Fizz" : "" } + (n % 5 == 0 ? "Buzz" : "");
    if (result.empty())
        return std::to_string(n);
    else
        return result;
    */

    if (n % 15 == 0) {
        return "FizzBuzz";
    } else if (n % 5 == 0) {
        return "Buzz";
    } else if (n % 3 == 0) {
        return "Fizz";
    } else {
        return std::to_string(n);
    }
}

TEST(FizzBuzzTest, fizz_buzz_compile_time)
{
    std::string expected;
    for (int n = 0; n < 100; ++n) {
        expected += runtime_fizzbuzz(n + 1) + "\n";
    }

    std::string const actual = workshop::fizzbuzz_t<1>::value;
    EXPECT_EQ(expected, actual);
}

TEST(FizzBuzzTest, fizz_buzz)
{
    EXPECT_EQ("1", runtime_fizzbuzz(1));
    EXPECT_EQ("Fizz", runtime_fizzbuzz(3));
    EXPECT_EQ("4", runtime_fizzbuzz(4));
    EXPECT_EQ("Buzz", runtime_fizzbuzz(5));
    EXPECT_EQ("Fizz", runtime_fizzbuzz(9));
    EXPECT_EQ("Buzz", runtime_fizzbuzz(10));
    EXPECT_EQ("FizzBuzz", runtime_fizzbuzz(15));
    EXPECT_EQ("FizzBuzz", runtime_fizzbuzz(30));
}

int identity(int n)
{
    return n;
}

template <int N>
struct t_identity {
    constexpr static int const value = N;
};

int add(int a, int b)
{
    return a + b;
}

template <int A, int B>
struct t_add {
    constexpr static int const value = A + B;
};

template <int A, int B>
constexpr static int const t_add_v = t_add<A, B>::value;

void foo()
{
    auto const answer = t_add_v<23, 19>;
}
