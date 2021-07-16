#include "World.hxx"

#include <stdexcept>

namespace {
	void validateArguments(int const width, int const height) {
		if (width * height < gol::MIN_CELLS) {
			throw std::invalid_argument{ "The world is too small!" };
		}
		else if (width < gol::MIN_DIMENSION) {
			throw std::invalid_argument{ "The width is too small!" };
		}
		else if (height < gol::MIN_DIMENSION) {
			throw std::invalid_argument{ "The height is too small!" };
		}
	}

	bool isInWorld(int x, int y, int width, int height) {
		return (x >= 0 && y >= 0 && x < width && y < height);
	}
}

namespace gol {
	World::World(
		Width const width /* = { DEFAULT_WIDTH } */,
		Height const height /* = { DEFAULT_HEIGHT } */
	)
		: m_width{ width.value }, m_height{ height.value }
	{
		validateArguments(m_width, m_height);
		m_cells.resize(m_width * m_height, CellState::Dead);
	}

	int World::width() const
	{
		return m_width;
	}

	int World::height() const
	{
		return m_height;
	}

	CellState World::getCell(int const x, int const y) const {
		if (!isInWorld(x, y, m_width, m_height)) {
			return CellState::Dead;
		}
		return m_cells[y * m_width + x];
	}

	void World::setCell(int x, int y, CellState state)
	{
		if (isInWorld(x, y, m_width, m_height)) {
			m_cells[y * m_width + x] = state;
		}
	}
}
