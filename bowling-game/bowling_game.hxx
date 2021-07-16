#pragma once

#include <vector>

class BowlingGame final {
public:
	constexpr static int const MAX_ROLLS = 21;
	constexpr static int const MAX_FRAMES = 10;
	constexpr static int const MAX_PINS = 10;

	BowlingGame();

	void roll(int pins);
	int score() const;

private:
	std::vector<int> rolls;

	static bool isStrike(int firstInFrame);
	static bool isSpare(int firstInFrame, int secondInFrame);
};
