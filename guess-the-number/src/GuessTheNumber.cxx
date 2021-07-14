#include "GuessTheNumber.hxx"

#include <iostream>
#include <string>

GuessTheNumber::GuessTheNumber(RandomNumberGenerator& rng)
	: rng{ rng }
{
}

void GuessTheNumber::run() {
	do {
		playSingleGame();
	} while (keepRunning());
}

bool GuessTheNumber::keepRunning()
{
	std::cout << "Play again? (yes/no)\n";
	std::string response;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::getline(std::cin, response);

	return response == "yes";
}

void GuessTheNumber::playSingleGame()
{
	showIntro();

	int const number = rng.getNextNumber();
	int tries = 0;

	for (;;) {
		++tries;

		int const guess = requestGuess(tries);

		CheckResult const result = checkGuess(guess, number);
		printResult(number, tries, result);
		if (result == CheckResult::Equal) break;
	}
}

CheckResult GuessTheNumber::checkGuess(int const guess, int const number)
{
	return
		guess == number ? CheckResult::Equal :
		guess < number ? CheckResult::Greater :
		CheckResult::Less;
}

void GuessTheNumber::printResult(int const number, int const tries, CheckResult const result) {
	switch (result) {
	case CheckResult::Equal:
		std::cout << "Congratulations, you found the number "
			<< number << " after " << tries << " tries.\n";
		break;
	case CheckResult::Greater:
		std::cout << "The searched number is greater than your guess.\n";
		break;
	case CheckResult::Less:
		std::cout << "The searched number is less than your guess.\n";
		break;
	}
}

int GuessTheNumber::requestGuess(int tries)
{
	int guess;
	do {
		std::cout << "Guess #" << tries << ": ";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	} while (!(std::cin >> guess));
	return guess;
}

void GuessTheNumber::showIntro()
{
	std::cout << "Guess the number (between "
		<< rng.getMinValue() << " and " << rng.getMaxValue() << "):\n";
}
