#include "StdRandomizer.hxx"

namespace gol {
	void StdRandomizer::randomizeWorld(World& world) {
		auto const nextCellState = [this]() {
			return dist(generator) ? CellState::Alive : CellState::Dead;
		};

		// TODO: add checks for ratios (min 10% alive, max 90% alive)
		// statistically we will almost always have 50/50 anyway
		for (int x = 0; x < world.width(); ++x) {
			for (int y = 0; y < world.height(); ++y) {
				world.setCell(x, y, nextCellState());
			}
		}
	}
}
