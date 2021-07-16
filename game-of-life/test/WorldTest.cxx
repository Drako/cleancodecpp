#include <gtest/gtest.h>

#include <World.hxx>

#include <stdexcept>

using namespace gol;

TEST(WorldTest, worldCanBeConstructed) {
	World world{};
	EXPECT_EQ(DEFAULT_WIDTH, world.width());
	EXPECT_EQ(DEFAULT_HEIGHT, world.height());
}

TEST(WorldTest, worldCanBeConstructedWithSize) {
	int const WIDTH = 23;
	int const HEIGHT = 42;

	World world{ {WIDTH}, {HEIGHT} };
	EXPECT_EQ(WIDTH, world.width());
	EXPECT_EQ(HEIGHT, world.height());
}

TEST(WorldTest, worldMustBeBigEnough) {
	auto const code = []() {
		int const WIDTH = DEFAULT_WIDTH - 1;
		int const HEIGHT = DEFAULT_HEIGHT - 1;
		World{ {WIDTH}, {HEIGHT} };
	};

	ASSERT_THROW(code(), std::invalid_argument);
}

TEST(WorldTest, widthMustBeBigEnough) {
	auto const code = []() {
		int const WIDTH = MIN_DIMENSION - 1;
		int const HEIGHT = MIN_CELLS;
		World{ {WIDTH}, {HEIGHT} };
	};

	ASSERT_THROW(code(), std::invalid_argument);
}

TEST(WorldTest, heightMustBeBigEnough) {
	auto const code = []() {
		int const WIDTH = MIN_CELLS;
		int const HEIGHT = MIN_DIMENSION - 1;
		World{ {WIDTH}, {HEIGHT} };
	};

	ASSERT_THROW(code(), std::invalid_argument);
}

TEST(WorldTest, canAccessCellState) {
	World world{};

	world.setCell(0, 0, CellState::Alive);
	EXPECT_EQ(CellState::Alive, world.getCell(0, 0));

	world.setCell(1, 1, CellState::Dead);
	EXPECT_EQ(CellState::Dead, world.getCell(1, 1));

	world.setCell(0, 2, CellState::Alive);
	EXPECT_EQ(CellState::Alive, world.getCell(0, 2));
}

TEST(WorldTest, cellsOutsideOfWorldAreDead) {
	World world{};
	EXPECT_EQ(CellState::Dead, world.getCell(DEFAULT_WIDTH, DEFAULT_HEIGHT));
}

TEST(WorldTest, settingCellOutsideWorldDoesNotCrash) {
	World world{};
	EXPECT_NO_FATAL_FAILURE(
		world.setCell(DEFAULT_WIDTH, DEFAULT_HEIGHT, CellState::Alive)
	);
}
