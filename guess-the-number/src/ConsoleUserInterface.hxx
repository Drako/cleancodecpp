#pragma once

#include "UserInterface.hxx"
#include "RandomNumberGenerator.hxx"

#include <iosfwd>

enum class InputPolicy {
	RESET,
	DONT_RESET,
};

class ConsoleUserInterface : public UserInterface {
public:
	ConsoleUserInterface(
		std::ostream& out, std::istream& in,
		InputPolicy inputPolicy = InputPolicy::RESET
	);

	int requestGuess(int tries) override;
	bool keepRunning() override;

	void showIntro(RandomNumberGenerator const& rng) override;
	void showResult(int number, int tries, CheckResult result) override;

private:
	std::ostream& out;
	std::istream& in;
	InputPolicy inputPolicy;

	void resetInput();
};
