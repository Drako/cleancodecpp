#include <gtest/gtest.h>

// TODO: make more accessible

#include <string>
#include <utility>

namespace workshop {
template <char... Characters>
struct string final {
    constexpr static char const value[] = { Characters..., '\0' };
};

template <int N>
struct fizzbuzz final {
    using type = string<>;
};

// alias, damit man nicht "typename X::type" schreiben muss
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

// int identity(int n) { return n; }
template <int N>
struct t_identity final {
    constexpr static int const value = N;
};

int add(int a, int b)
{
    return a + b;
}

template <int A, int B>
struct t_add final {
    constexpr static int const value = A + B;
};

// alias, damit man ::value nicht schreiben muss
template <int A, int B>
constexpr static int const t_add_v = t_add<A, B>::value;

int sum(int size, int* numbers)
{
    if (size == 0)
        return 0;
    else
        return numbers[0] + sum(size - 1, numbers + 1);
}

// ab C++11

// sum :: Int[] -> Int
template <int... Numbers>
struct t_sum;

// sum [] = 0
template <>
struct t_sum<> {
    constexpr static const int value = 0;
};

// sum (head:tail) = head + sum tail
template <int Head, int... Tail>
struct t_sum<Head, Tail...> {
    constexpr static const long value = Head + t_sum<Tail...>::value;
};

template <int... Numbers>
constexpr static auto const t_sum_v = t_sum<Numbers...>::value;

// This is C++17
// template <int... Numbers>
// constexpr static int const t_sum_v = (0 + ... + Numbers);

/*
 * Pseudocode für Template max_type
type max(type a, type b)
{
    return sizeof(a) > sizeof(b) ? a : b;
}
*/

namespace detail {
// if_type entspricht ternärem Operator mit Typen
// type if_type(bool cond, type a, type b) { return cond ? a : b; }
template <bool Condition, typename IfType, typename ElseType>
struct if_type final {
    using type = IfType;
};

template <typename IfType, typename ElseType>
struct if_type<false, IfType, ElseType> final {
    using type = ElseType;
};
}

template <typename A, typename B>
struct max_type final {
    using type = typename detail::if_type<
        (sizeof(A) > sizeof(B)),
        A, B>::type;
};

// Klassentemplate
/*
template <typename T>
class vector final {
    T operator[](std::size_t index) const
    {
        return data[index];
    }

    T* data;
};

static_assert(sizeof(char) == 1);

template <>
class vector<bool> final {
    struct proxy {
        operator bool()
        {
        }
    };

    bool& operator[](std::size_t index)
    {
        return data[index];
    }
};
*/

#include <type_traits>

// Funktionstemplate
template <typename Out, typename... Args>
auto stream(Out& out, Args&&... args)
    -> std::enable_if_t<std::is_base_of_v<std::ostream, Out>, Out&>
{
    return (out << ... << args);
}

// Funktionstemplate
template <typename T>
auto sum(T a, T b)
    -> std::enable_if_t<std::is_integral_v<T>, T>
{
    return a + b;
}

struct Foo {
    void frobnicate();
};

struct Bar {
};

/*
template <typename T>
struct has_frobnicate {
    using false_type = char;
    using true_type = struct {
        char dummy[2];
    };
    static_assert(sizeof(true_type) != sizeof(false_type));

    static false_type test(...);

    template <typename U = T>
    static true_type test(int, decltype(U::frobnicate) = nullptr);

    constexpr static const bool value = sizeof(test(0)) == sizeof(true_type);
};
*/

void foo()
{
    //static_assert(has_frobnicate<Foo>::value);
    //static_assert(!has_frobnicate<Bar>::value);

    stream(std::cout, 23, 42, "hallo");

    sum(23, 42);
    //sum(13.0, 14.0);

    using MyInt = typename max_type<int, long>::type;

    static_assert(std::is_same_v<int, std::remove_cv_t<decltype(t_sum_v<>)>>);
    static_assert(std::is_same_v<long, std::remove_cv_t<decltype(t_sum_v<23>)>>);
    static_assert(std::is_same_v<long, std::remove_cv_t<decltype(t_sum_v<23, 42>)>>);
}

#include <utility>

// && here means universal reference...
// it is either a normal reference or an rvalue one
template <typename T, typename... Args>
T construct(Args&&... args)
{
    return T { std::forward<Args>(args)... };
}
