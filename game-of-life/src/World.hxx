#pragma once

#include "DllInterface.hxx"
#include "CellState.hxx"

#include <vector>

namespace gol {
	// strong typedefs
	struct Width { int value; };
	struct Height { int value; };

	constexpr static int const DEFAULT_WIDTH = 10;
	constexpr static int const DEFAULT_HEIGHT = 10;

	constexpr static int const MIN_CELLS = 100;
	constexpr static int const MIN_DIMENSION = 3;

	class GOL_DLL_INTERFACE World final {
	public:
		/**
		 * @throw std::invalid_argument if the size of the field is less than MIN_CELLS cells.
		 * @throw std::invalid_argument if either dimension is smaller than MIN_DIMENSION.
		 */
		World(
			Width width = { DEFAULT_WIDTH },
			Height height = { DEFAULT_HEIGHT }
		);

		int width() const;
		int height() const;

		/**
		 * Returns the cell state or CellState::Dead for cells outside of the world.
		 */
		CellState getCell(int x, int y) const;
		void setCell(int x, int y, CellState state);

	private:
		int m_width;
		int m_height;
		std::vector<CellState> m_cells;
	};
}
