#pragma once

#include "RandomNumberGenerator.hxx"
#include "GameIO.hxx"

#include <sdi/component.hxx>

class GuessTheNumber
{
public:
  using dependencies = sdi::dependencies<RandomNumberGenerator, GameIO>;

  GuessTheNumber(RandomNumberGenerator &rng, GameIO &io);

  void run();

private:
  RandomNumberGenerator &rng;
  GameIO &io;
};
