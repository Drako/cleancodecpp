#pragma once

#include "DllInterface.hxx"

namespace gol {
	class World;

	struct GOL_DLL_INTERFACE Randomizer {
		virtual ~Randomizer() noexcept = default;

		virtual void randomizeWorld(World& world) = 0;
	};
}
