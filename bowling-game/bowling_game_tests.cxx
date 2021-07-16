#include <gtest/gtest.h>

#include "bowling_game.hxx"

// #define UNUSED(x) ((void)x)

class BowlingGameTest : public ::testing::Test {
public:
	BowlingGame game{};

	void rollMany(int pins, int count) {
		for (int n = 0; n < count; ++n)
			game.roll(pins);
	}

	void rollStrike()
	{
		game.roll(BowlingGame::MAX_PINS);
	}

	void rollSpare(int firstRoll = 5) {
		game.roll(firstRoll);
		game.roll(BowlingGame::MAX_PINS - firstRoll);
	}
};

TEST_F(BowlingGameTest, gutterGame) {
	rollMany(0, 20);
	EXPECT_EQ(0, game.score());
}

TEST_F(BowlingGameTest, oneSuccessfulRegularRoll) {
	game.roll(3);
	rollMany(0, 19);
	EXPECT_EQ(3, game.score());
}

TEST_F(BowlingGameTest, oneSpare) {
	rollSpare();
	game.roll(5);
	rollMany(0, 17);
	EXPECT_EQ(20, game.score());
}

TEST_F(BowlingGameTest, noSpareBecauseCrossingFrames) {
	game.roll(0);
	rollSpare();
	game.roll(5);
	rollMany(0, 16);
	EXPECT_EQ(15, game.score());
}

TEST_F(BowlingGameTest, oneSpareAtEndOfGame) {
	rollMany(0, 18);
	rollSpare();
	game.roll(5);
	EXPECT_EQ(15, game.score());
}

TEST_F(BowlingGameTest, oneStrike) {
	rollStrike();
	game.roll(2);
	game.roll(3);
	rollMany(0, 16);
	EXPECT_EQ(20, game.score());
}

TEST_F(BowlingGameTest, strikeInLastFrame) {
	rollMany(0, 18);
	rollStrike();
	game.roll(2);
	game.roll(3);
	EXPECT_EQ(15, game.score());
}

TEST_F(BowlingGameTest, perfectGame) {
	rollMany(BowlingGame::MAX_PINS, 12);
	EXPECT_EQ(300, game.score());
}
