#pragma once

#include <random>

#include "RandomNumberGenerator.hxx"

// wann brauche ich einen Konstruktor:
// * wenn ich einen Basisklassenkonstruktor aufrufen muss
// * wenn mein Konstruktor Parameter hat

// POD = Plain Old Data
/*
struct Point {
	int x, y;
};

Point p{};

int a{};

Point p{0, 2};
Point p2 = p1;
*/

class StdRandomNumberGenerator final : public RandomNumberGenerator {
public:
	constexpr static int const MIN_VALUE = 1;
	constexpr static int const MAX_VALUE = 100;

	int getNextNumber() override {
		return dist(generator);
	};

	int getMinValue() const override {
		return MIN_VALUE;
	}

	int getMaxValue() const override {
		return MAX_VALUE;
	}

private:
	std::random_device rd;
	std::mt19937 generator{ rd() };
	std::uniform_int_distribution<> dist{ MIN_VALUE, MAX_VALUE };
};
