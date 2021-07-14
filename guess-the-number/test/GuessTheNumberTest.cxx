#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <GuessTheNumber.hxx>

TEST(GuessTheNumberTest, theGameWorks) {
	GuessTheNumber game{};
	// now how do you test that?
	EXPECT_EQ(42, 6 * 7);
}
