# Notes about Game of Life

```cpp
enum class CellState {
	Dead,
	Alive
}

struct World final {
	std::vector<CellState> cells(width * height);
}
```

// I/O
struct UserInterface // interface
 virtual ~UserInterface() noexcept = default;
class ConsoleUserInterface

// Spiellogik/Regeln
class Game
step()
countLivingNeighbors(int x, int y)
getNextCellState(CellState currentState, int livingNeighbors)
 - bool shouldDie(CellState currentState, int livingNeighbors)
 - bool shouldBeBorn(CellState currentState, int livingNeighbors)
