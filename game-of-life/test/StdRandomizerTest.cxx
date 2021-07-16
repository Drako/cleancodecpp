#include <gtest/gtest.h>

#include <StdRandomizer.hxx>

TEST(StdRandomizerTest, shouldEvenlyDistributeAliveAndDead) {
	int const WIDTH = 10;
	int const HEIGHT = 10;

	gol::World world{ {WIDTH}, {HEIGHT} };
	gol::StdRandomizer rnd{};

	rnd.randomizeWorld(world);

	int aliveCount{ 0 };
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			if (world.getCell(x, y) == gol::CellState::Alive) {
				++aliveCount;
			}
		}
	}

	EXPECT_LE(40, aliveCount);
	EXPECT_GE(60, aliveCount);
}
