#pragma once

#include "DllInterface.hxx"
#include "World.hxx"

namespace gol {
	struct GOL_DLL_INTERFACE Randomizer {
		virtual ~Randomizer() noexcept = default;

		virtual void randomizeWorld(World& world) = 0;
	};
}
