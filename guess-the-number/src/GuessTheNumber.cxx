#include "GuessTheNumber.hxx"

#include <iostream>
#include <string>

void GuessTheNumber::run() {
	bool keepRunning = true;
	while (keepRunning) {
		std::cout << "Guess the number (between 1 and 100):\n";

		int const number = dist(generator);
		int tries = 0;

		for (;;) {
			++tries;
			int guess;

			do {
				std::cout << "Guess #" << tries << ": ";
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
			} while (!(std::cin >> guess));

			if (guess == number) {
				std::cout << "Congratulations, you found the number "
					<< number << " after " << tries << " tries.\n";
				break;
			}
			else if (guess < number) {
				std::cout << "The searched number is greater than your guess.\n";
			}
			else {
				std::cout << "The searched number is less than your guess.\n";
			}
		}

		std::cout << "Play again? (yes/no)\n";
		std::string response;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::getline(std::cin, response);

		if (response != "yes") {
			keepRunning = false;
		}
	}
}
