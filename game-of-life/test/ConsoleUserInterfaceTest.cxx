#include <gtest/gtest.h>

#include <ConsoleUserInterface.hxx>
#include <World.hxx>

#include <sstream>

class ConsoleUserInterfaceTest : public ::testing::Test {
public:
	std::ostringstream out;
	std::istringstream in;
	gol::ConsoleUserInterface ui{ out, in };
};

TEST_F(ConsoleUserInterfaceTest, rendersEmptyWorld) {
	gol::World world{};
	ui.renderWorld(world);

	char const * const expected =
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n\n";
	EXPECT_EQ(expected, out.str());
}

TEST_F(ConsoleUserInterfaceTest, rendersCross) {
	gol::World world{};
	world.setCell(5, 1, gol::CellState::Alive);
	world.setCell(4, 2, gol::CellState::Alive);
	world.setCell(5, 2, gol::CellState::Alive);
	world.setCell(6, 2, gol::CellState::Alive);
	world.setCell(5, 3, gol::CellState::Alive);

	ui.renderWorld(world);

	char const * const expected =
		"          \n"
		"     #    \n"
		"    ###   \n"
		"     #    \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n"
		"          \n\n";
	EXPECT_EQ(expected, out.str());
}

TEST_F(ConsoleUserInterfaceTest, rendersFullWorld) {
	gol::World world{};
	for (int y = 0; y < world.height(); ++y) {
		for (int x = 0; x < world.width(); ++x) {
			world.setCell(x, y, gol::CellState::Alive);
		}
	}

	ui.renderWorld(world);

	char const * const expected =
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n"
		"##########\n\n";
	EXPECT_EQ(expected, out.str());
}

TEST_F(ConsoleUserInterfaceTest, waitsForUserInteraction) {
	//in.str("\n");
	ASSERT_NO_FATAL_FAILURE(ui.waitForUserInteraction());
}
