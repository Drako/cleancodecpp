#pragma once

#include "DllInterface.hxx"
#include "UserInterface.hxx"

#include <iosfwd>

namespace gol {
	class GOL_DLL_INTERFACE ConsoleUserInterface final : public UserInterface{
	public:
		ConsoleUserInterface(std::ostream& out, std::istream& in);

		void renderWorld(World const& world) override;
		void waitForUserInteraction() override;

	private:
		std::ostream& m_out;
		std::istream& m_in;
	};
}
