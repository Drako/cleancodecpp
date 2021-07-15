#include "GuessTheNumber.hxx"
#include "StdRandomNumberGenerator.hxx"
#include "ConsoleUserInterface.hxx"

#include <iostream>

int main() {
	StdRandomNumberGenerator rng;
	ConsoleUserInterface ui{std::cout, std::cin};
	GuessTheNumber game{rng, ui};
	game.run();
	return 0;
}
