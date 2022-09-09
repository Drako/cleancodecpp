#include "GuessTheNumber.hxx"
#include "StdRandomNumberGenerator.hxx"
#include "Console.hxx"
#include "GuessTheNumberIO.hxx"

#include <sdi.hxx>

struct Width final { int value; };
struct Height final { int value; };

class World final {
  int width;
  int height;

public:
  using dependencies = sdi::dependencies<Width, Height>;

  World(Width width, Height height)
  : width{width.value}, height{height.value}
  {
  }
};

int main()
{
  using world_container = sdi::container<sdi::known_types<Width, Height, World>>;
  auto world = world_container::use_threadsafe([](world_container& c){
    c.emplace<Width>(1024);
    c.emplace<Height>(768);
    return c.resolve<World>();
  });

  auto game = sdi::container<
    sdi::known_types<Console, GuessTheNumberIO, StdRandomNumberGenerator, GuessTheNumber>>
  ::instance().resolve<GuessTheNumber>();
  game.run();
  return 0;
}
