#pragma once

#include "RandomNumberGenerator.hxx"

#include <random>

class StdRandomNumberGenerator final: public RandomNumberGenerator
{
  std::mt19937 generator{std::random_device{}()};
  std::uniform_int_distribution<> dist{1, 100};

public:
  int generate() override;
};
