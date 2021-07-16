// SUT = Subject Under Test
#include <gtest/gtest.h>

#include <ConsoleUserInterface.hxx>

#include <sstream>
#include <tuple>

#include "MockRandomNumberGenerator.hxx"

namespace t = testing;

class ConsoleUserInterfaceTest : public t::Test {
public:
	std::ostringstream out;
	std::istringstream in;
	ConsoleUserInterface ui{ out, in, InputPolicy::DONT_RESET };
};

using ShowIntroParameters = std::tuple<int, int, char const*>;

struct ShowIntroTest : ConsoleUserInterfaceTest
	, t::WithParamInterface<ShowIntroParameters> {};

TEST_P(ShowIntroTest, showIntroShouldShowWantedNumberRange) {
	// init
	auto const[minValue, maxValue, message] = GetParam();

	MockRandomNumberGenerator rng;
	ON_CALL(rng, getMinValue())
		.WillByDefault(t::Return(minValue));
	EXPECT_CALL(rng, getMinValue());

	ON_CALL(rng, getMaxValue())
		.WillByDefault(t::Return(maxValue));
	EXPECT_CALL(rng, getMaxValue());

	// test
	ui.showIntro(rng);

	// verification
	EXPECT_EQ(message, out.str());
}

INSTANTIATE_TEST_SUITE_P(
	ConsoleUserInterfaceTest,
	ShowIntroTest,
	t::Values(
		std::make_tuple(1, 100, "Guess the number (between 1 and 100):\n"),
		std::make_tuple(23, 42, "Guess the number (between 23 and 42):\n"),
		std::make_tuple(-273, 100, "Guess the number (between -273 and 100):\n")
	)
);

using KeepRunningParameters = std::tuple<char const*, bool>;

struct KeepRunningTest : ConsoleUserInterfaceTest
	, t::WithParamInterface<KeepRunningParameters> {};

TEST_P(KeepRunningTest, keepRunningIfInputIsYes) {
	auto const[input, expected] = GetParam();
	in.str(input);
	EXPECT_EQ(expected, ui.keepRunning());
}

INSTANTIATE_TEST_SUITE_P(
	ConsoleUserInterfaceTest,
	KeepRunningTest,
	t::Values(
		std::make_tuple("yes", true),
		std::make_tuple("no", false),
		std::make_tuple("", false),
		std::make_tuple("1234567890", false),
		std::make_tuple("affe", false),
		std::make_tuple("@€", false)
	)
);
