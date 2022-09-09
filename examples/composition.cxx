struct PetrolEngine
{
  void start()
  {}
};

struct DieselEngine
{
  void start()
  {}
};

template<typename Engine>
struct Car: protected Engine
{
  void start()
  {
    Engine::start();
  }
};

struct Shape
{
};

struct Square: Shape
{
  int length;
};

struct Rectangle: Shape
{
  int width;
  int height;

  Rectangle(Square const &src)
    : width{src.length}, height{src.length}
  {
    int answer{42};

  }
};

