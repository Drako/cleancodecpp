#pragma once

#include "CheckResult.hxx"
#include "RandomNumberGenerator.hxx"
#include "UserInterface.hxx"

#include <random>

/**
 * Main class of the guess the number game.
 */
class GuessTheNumber
{
public:
	GuessTheNumber(
		RandomNumberGenerator& rng,
		UserInterface& ui
	);

	// Main
	void run();

	// Spiellogik
	void playSingleGame();
	CheckResult checkGuess(int guess, int number);

private:
	RandomNumberGenerator& rng;
	UserInterface& ui;
};
