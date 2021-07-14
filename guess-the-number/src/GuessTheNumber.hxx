#pragma once

#include "CheckResult.hxx"
#include "RandomNumberGenerator.hxx"

#include <random>

/**
 * Main class of the guess the number game.
 */
class GuessTheNumber
{
public:
	GuessTheNumber(RandomNumberGenerator& rng);

	// Main
	void run();

	// Spiellogik
	void playSingleGame();
	CheckResult checkGuess(int guess, int number);

	// User-Interface I/O
	int requestGuess(int tries);
	void showIntro();
	bool keepRunning();
	void printResult(int number, int tries, CheckResult result);

private:
	RandomNumberGenerator& rng;
};
