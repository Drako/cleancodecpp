#pragma once

#include "DllInterface.hxx"

namespace gol {
	class World;

	struct GOL_DLL_INTERFACE UserInterface {
		virtual ~UserInterface() noexcept = default;

		virtual void renderWorld(World const& world) = 0;
		virtual void waitForUserInteraction() = 0;
	};
}
