#include "ConsoleUserInterface.hxx"

#include "World.hxx"

#include <iostream>

namespace gol {
	ConsoleUserInterface::ConsoleUserInterface(std::ostream& out, std::istream& in)
		: m_out{ out }, m_in{ in }
	{}

	void ConsoleUserInterface::renderWorld(World const& world) {
		auto const cellChar = [](CellState const state) {
			return state == CellState::Alive ? '#' : ' ';
		};

		for (int y = 0; y < world.height(); ++y) {
			for (int x = 0; x < world.width(); ++x) {
				m_out << cellChar(world.getCell(x, y));
			}
			m_out << "\n";
		}
		m_out << "\n";
	}

	void ConsoleUserInterface::waitForUserInteraction() {
		m_in.clear();
		char buffer[80];
		m_in.getline(buffer, 80);
	}
}
