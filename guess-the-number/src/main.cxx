#include "GuessTheNumber.hxx"
#include "StdRandomNumberGenerator.hxx"

int main() {
	StdRandomNumberGenerator rng;
	GuessTheNumber game{rng};
	game.run();
	return 0;
}
