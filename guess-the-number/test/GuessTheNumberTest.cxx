#include <gtest/gtest.h>

#include <GuessTheNumber.hxx>

#include <tuple>

#include "MockRandomNumberGenerator.hxx"

/*
TEST(GuessTheNumberTest, answerIs42) {
	// init
	int factor1 = 6, factor2 = 7;

	// test
	int answer = factor1 * factor2;

	// verify result
	EXPECT_EQ(42, answer);
}
*/

// Fixture
class GuessTheNumberTest : public ::testing::Test {
public:
	// shared init
	MockRandomNumberGenerator rng;
	GuessTheNumber game{ rng };
};

TEST_F(GuessTheNumberTest, showIntroCanBeRun) {
	EXPECT_NO_FATAL_FAILURE(game.showIntro());
}

// Marker for set of parameters
struct NumberFoundParameters : GuessTheNumberTest
	, ::testing::WithParamInterface<int> {};

// Test using specified marker
TEST_P(NumberFoundParameters, equalNumbersShouldYieldEqualResult) {
	int const number = GetParam();
	EXPECT_EQ(CheckResult::Equal, game.checkGuess(number, number));
}

// Declaration of parameter set for specified marker
INSTANTIATE_TEST_SUITE_P(
	GuessTheNumberTest,
	NumberFoundParameters,
	::testing::Range(1, 101)
);

using ComparisonParameters = std::tuple<int, int>;

struct NumberLessThanGuessParameters : GuessTheNumberTest
	, ::testing::WithParamInterface<ComparisonParameters> {};

/*
struct NumberGreaterThanGuessParameters : GuessTheNumberTest
	, ::testing::WithParamInterface<ComparisonParameters> {};
*/

TEST_P(NumberLessThanGuessParameters, numberLessThanGuessShouldYieldLess) {
	auto const [number, guess] = GetParam();
	EXPECT_EQ(CheckResult::Less, game.checkGuess(guess, number));
}

// TEST_P(NumberGreaterThanGuessParameters, numberGreaterThanGuessShouldYieldGreater) {
TEST_P(NumberLessThanGuessParameters, numberGreaterThanGuessShouldYieldGreater) {
	auto const[guess, number] = GetParam();
	EXPECT_EQ(CheckResult::Greater, game.checkGuess(guess, number));
}

INSTANTIATE_TEST_SUITE_P(
	GuessTheNumberTest,
	NumberLessThanGuessParameters,
	::testing::Values(
		std::make_tuple(23, 42),
		std::make_tuple(42, 1337)
	)
);

/*
INSTANTIATE_TEST_SUITE_P(
	GuessTheNumberTest,
	NumberGreaterThanGuessParameters,
	::testing::Values(
		std::make_tuple(42, 23),
		std::make_tuple(1337, 42)
	)
);
*/
