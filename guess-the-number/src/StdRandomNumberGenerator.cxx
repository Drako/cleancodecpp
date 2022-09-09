#include "StdRandomNumberGenerator.hxx"

int StdRandomNumberGenerator::generate()
{
  return dist(generator);
}
