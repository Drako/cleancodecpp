#pragma once

#include <random>

class GuessTheNumber
{
public:
	void run();

private:
	std::random_device rd;
	std::mt19937 generator{ rd() };
	std::uniform_int_distribution<> dist{ 1, 100 };
};
