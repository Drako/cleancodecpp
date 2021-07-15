#pragma once

#include "UserInterface.hxx"
#include "RandomNumberGenerator.hxx"

#include <iosfwd>

class ConsoleUserInterface final : public UserInterface {
public:
	ConsoleUserInterface(std::ostream& out, std::istream& in);

	int requestGuess(int tries) override;
	bool keepRunning() override;

	void showIntro(RandomNumberGenerator const& rng) override;
	void showResult(int number, int tries, CheckResult result) override;

private:
	std::ostream& out;
	std::istream& in;
};
