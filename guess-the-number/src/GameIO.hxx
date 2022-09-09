#pragma once

enum class Result;

struct GameIO
{
  virtual ~GameIO() noexcept = default;

  virtual void printIntro() = 0;
  virtual int queryGuess(int tries) = 0;
  virtual void printResult(Result result, int number, int tries) = 0;
  virtual bool keepRunning() = 0;
};
