#include <gtest/gtest.h>

#include "GuessTheNumberIO.hxx"
#include "IODeviceMock.hxx"

#include <string>
#include <iomanip>
#include <iostream>
using namespace std::string_literals;

class GuessTheNumberIOTest: public testing::Test
{
protected:
  IODeviceMock io{};
  GuessTheNumberIO sut{io};
};

TEST_F(GuessTheNumberIOTest, introIsCorrect)
{
  EXPECT_CALL(io, print_line("Guess the number (between 1 and 100):"s));
  sut.printIntro();
}

struct KeepRunningParams final
{
  std::string input;
  bool expected;
};

std::ostream &operator<<(std::ostream &os, KeepRunningParams const &krp)
{
  return os << "[input=\"" << krp.input << "\", expected=" << std::boolalpha << krp.expected << "]";
}

class GuessTheNumberIOTest_KeepRunning: public GuessTheNumberIOTest, public testing::WithParamInterface<KeepRunningParams>
{
};

INSTANTIATE_TEST_SUITE_P(KeepRunningParams, GuessTheNumberIOTest_KeepRunning,
                         testing::Values(
                           KeepRunningParams{"yes", true},
                           KeepRunningParams{"no", false}
                         ));

TEST_P(GuessTheNumberIOTest_KeepRunning, keepRunningYieldsCorrectResult)
{
  auto const params = GetParam();
  EXPECT_CALL(io, print_line("Play again? (yes/no)"s));
  EXPECT_CALL(io, read_line())
    .WillOnce([&params]{ return params.input; });
  EXPECT_EQ(sut.keepRunning(), params.expected);
}
