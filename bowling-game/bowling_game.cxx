#include "bowling_game.hxx"

BowlingGame::BowlingGame() {
	rolls.reserve(MAX_ROLLS);
}

void BowlingGame::roll(int pins) {
	rolls.push_back(pins);
}

int BowlingGame::score() const {
	int sum = 0;
	int frameStart = 0;
	for (int currentFrame = 0; currentFrame < MAX_FRAMES; ++currentFrame) {
		int const firstInFrame = rolls[frameStart];
		int const secondInFrame = rolls[frameStart + 1];
		sum += firstInFrame + secondInFrame;
		++frameStart;

		if (isStrike(firstInFrame)) {
			sum += rolls[frameStart + 1];
		}
		else if (isSpare(firstInFrame, secondInFrame)) {
			sum += rolls[frameStart + 1];
			++frameStart;
		}
		else {
			++frameStart;
		}
	}
	return sum;
}

bool BowlingGame::isStrike(int firstInFrame)
{
	return firstInFrame == MAX_PINS;
}

bool BowlingGame::isSpare(int firstInFrame, int secondInFrame)
{
	return firstInFrame + secondInFrame == MAX_PINS;
}
