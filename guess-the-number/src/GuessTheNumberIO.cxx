#include "GuessTheNumberIO.hxx"
#include "Result.hxx"
#include "IODevice.hxx"

#include <string>
#include <sstream>

GuessTheNumberIO::GuessTheNumberIO(IODevice &io)
  : io{io}
{
}

void GuessTheNumberIO::printIntro()
{
  io.print_line("Guess the number (between 1 and 100):");
}

int GuessTheNumberIO::queryGuess(int tries)
{
  int guess;
  do {
    io.print_line("Guess #" + std::to_string(tries) + ": ");
  }
  while (!io.read_int(guess));
  return guess;
}

void GuessTheNumberIO::printResult(Result result, int number, int tries)
{
  switch (result) {
  case Result::Equal: {
    std::ostringstream formatter;
    formatter << "Congratulations, you found the number "
              << number << " after " << tries << " tries.";
    io.print_line(formatter.str());
  }
    break;
  case Result::LessThan:
    io.print_line("The searched number is greater than your guess.");
    break;
  case Result::GreaterThan:
    io.print_line("The searched number is less than your guess.");
    break;
  }
}

bool GuessTheNumberIO::keepRunning()
{
  io.print_line("Play again? (yes/no)");
  return io.read_line() == "yes";
}
