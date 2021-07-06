#pragma once

#include <vector>

class BowlingGame {
public:
    static constexpr int const MAX_FRAMES = 12;
    static constexpr int const MAX_PINS = 10;
    static constexpr int const MAX_ROLLS = MAX_FRAMES * 2;

    BowlingGame();

    void roll(int pins);

    // must be called at end of game
    // undefined behaviour otherwise
    int score() const;

    inline void roll_many(int count, int pins)
    {
        while (count-- != 0) {
            roll(pins);
        }
    }

    inline void roll_zeroes_until_end()
    {
        roll_many(MAX_ROLLS - static_cast<int>(m_rolls.size()), 0);
    }

    inline void roll_spare(int pins = 5)
    {
        roll(pins);
        roll(MAX_PINS - pins);
    }

    inline void roll_strike()
    {
        roll(MAX_PINS);
    }

private:
    std::vector<int> m_rolls;

    bool is_spare(int first, int second) const;
    bool is_strike(int first) const;
};
