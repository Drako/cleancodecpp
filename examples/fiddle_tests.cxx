#include <gtest/gtest.h>

// #include <hippomocks.h>

#include <cstdio>

// mocking free functions

void greet()
{
    std::puts("Hello world!");
}

int old_multiplicate(int a, int b)
{
    int product { 1 };
    for (int n = 0; n < b; ++n) {
        product += a;
    }
    return product;
}

int multiplicate(int a, int b)
{
    return a * b;
}

TEST(MultTest, behaviour_should_stay)
{
    EXPECT_EQ(old_multiplicate(0, 42), multiplicate(0, 42));
    EXPECT_EQ(old_multiplicate(23, 42), multiplicate(23, 42));
}

/*
TEST(GreetTest, greet_should_greet_everyone)
{
    MockRepository mocks;
    char const* output { nullptr };
    mocks.ExpectCallFunc(std::puts).With(In(output)).Return(0);

    greet();

    EXPECT_EQ("Hello world!", output);
}
*/
