#include "bowling_game.hxx"

#include <cassert>

BowlingGame::BowlingGame()
{
    m_rolls.reserve(MAX_ROLLS + 1);
}

void BowlingGame::roll(int pins)
{
    m_rolls.push_back(pins);
}

int BowlingGame::score() const
{
    int sum {};
    std::size_t current_roll { 0u };
    for (int frame = 0; frame < MAX_FRAMES; ++frame) {
        int const first_in_frame = m_rolls[current_roll];
        int const second_in_frame = m_rolls[current_roll + 1];
        sum += first_in_frame + second_in_frame;

        if (is_spare(first_in_frame, second_in_frame)) {
            sum += m_rolls[current_roll + 2];
            current_roll += 2;
        } else if (is_strike(first_in_frame)) {
            sum += m_rolls[current_roll + 2];
            current_roll += 1;
        } else {
            current_roll += 2;
        }
    }
    return sum;
}

bool BowlingGame::is_spare(int first, int second) const
{
    return first + second == MAX_PINS;
}

bool BowlingGame::is_strike(int first) const
{
    return first == MAX_PINS;
}
