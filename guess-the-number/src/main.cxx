#include "GuessTheNumber.hxx"
#include "StdRandomNumberGenerator.hxx"
#include "ConsoleUserInterface.hxx"

#include <iostream>

#include <boost/di.hpp>
namespace di = boost::di;

int main() {
	/* - manual dependency management
	StdRandomNumberGenerator rng;
	ConsoleUserInterface ui{ std::cout, std::cin };
	GuessTheNumber game{ rng, ui };
	game.run();
	*/

	auto const injector = di::make_injector(
		di::bind<std::ostream>.to(std::cout),
		di::bind<std::istream>.to(std::cin),
		di::bind<RandomNumberGenerator>.to<StdRandomNumberGenerator>(),
		di::bind<UserInterface>.to<ConsoleUserInterface>()
	);

	auto game = injector.create<std::unique_ptr<GuessTheNumber>>();
	game->run();
	return 0;
}
