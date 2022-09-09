#include "GuessTheNumber.hxx"
#include "Result.hxx"

#include <iostream>
#include <string>

GuessTheNumber::GuessTheNumber(RandomNumberGenerator &rng, GameIO &io)
  : rng{rng}, io{io}
{
}

void GuessTheNumber::run()
{
  do {
    io.printIntro();

    // Random value source
    int const number = rng.generate();
    int tries = 0;

    for (;;) {
      ++tries;

      // I/O
      int const guess = io.queryGuess(tries);

      Result result;
      if (guess == number) { // Validation
        result = Result::Equal;
      }
      else if (guess < number) { // Validation
        result = Result::LessThan;
      }
      else { // Validation
        result = Result::GreaterThan;
      }
      io.printResult(result, number, tries);

      if (result == Result::Equal) { // flow control
        break;
      }
    }
  }
  while (io.keepRunning()); // Flow control
}
