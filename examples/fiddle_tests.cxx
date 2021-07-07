#include <gtest/gtest.h>

#include <hippomocks.h>

#include <cstdio>

void greet()
{
    std::puts("Hello world!");
}

TEST(GreetTest, greet_should_greet_everyone)
{
    MockRepository mocks;
    char const* output { nullptr };
    mocks.ExpectCallFunc(std::puts).With(In(output)).Return(0);

    greet();

    EXPECT_EQ("Hello world!", output);
}
