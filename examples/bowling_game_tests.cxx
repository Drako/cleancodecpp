#include "bowling_game.hxx"

#include <gtest/gtest.h>

class BowlingGameTest : public ::testing::Test {
public:
    BowlingGame game {};
};

// Gutter: side lanes where you miss all pins
// Gutter game: no points
TEST_F(BowlingGameTest, a_gutter_game_should_have_a_score_of_0)
{
    game.roll_zeroes_until_end();
    EXPECT_EQ(0, game.score());
}

// only one point was made
TEST_F(BowlingGameTest, one_game)
{
    game.roll(1);
    game.roll_zeroes_until_end();
    EXPECT_EQ(1, game.score());
}

// only a spare was rolled
TEST_F(BowlingGameTest, one_spare_game)
{
    game.roll_spare();
    game.roll(2);
    game.roll_zeroes_until_end();
    EXPECT_EQ(14, game.score());
}

// only a spare was rolled at end of game
TEST_F(BowlingGameTest, last_frame_has_3_rolls_if_spare)
{
    game.roll_many(BowlingGame::MAX_ROLLS - 2, 0);
    game.roll_spare();
    game.roll(2);
    EXPECT_EQ(12, game.score());
}

// only a strike was rolled
TEST_F(BowlingGameTest, one_strike)
{
    game.roll_strike();
    game.roll(2);
    game.roll(4);
    game.roll_zeroes_until_end();
    EXPECT_EQ(22, game.score());
}

TEST_F(BowlingGameTest, one_strike_2)
{
    game.roll_strike();
    game.roll(0);
    game.roll(4);
    game.roll_zeroes_until_end();
    EXPECT_EQ(18, game.score());
}

// all strikes were rolled
TEST_F(BowlingGameTest, perfect_game)
{
    game.roll_many(14, BowlingGame::MAX_PINS);
    EXPECT_EQ(360, game.score());
}
