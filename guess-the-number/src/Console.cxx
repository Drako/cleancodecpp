#include "Console.hxx"

#include <iostream>

std::string Console::read_line()
{
  std::string line;
  std::cin.clear();
  std::cin.ignore(std::cin.rdbuf()->in_avail());
  while (line.empty()) {
    std::getline(std::cin, line);
  }
  return line;
}

bool Console::read_int(int& n)
{
  std::cin.clear();
  std::cin.ignore(std::cin.rdbuf()->in_avail());
  std::cin >> n;
  return !(std::cin.fail());
}

void Console::print_line(std::string const &message)
{
  std::cout << message << std::endl;
}
