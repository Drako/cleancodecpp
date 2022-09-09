#pragma once

#include "GameIO.hxx"

#include <sdi/component.hxx>

struct IODevice;

class GuessTheNumberIO: public GameIO
{
  IODevice &io;

public:
  using dependencies = sdi::dependencies<IODevice>;

  explicit GuessTheNumberIO(IODevice &io);

  void printIntro() override;
  int queryGuess(int tries) override;
  void printResult(Result result, int number, int tries) override;
  bool keepRunning() override;
};
