#pragma once

#include "DllInterface.hxx"
#include "Randomizer.hxx"

#include <random>

namespace gol {
	class GOL_DLL_INTERFACE StdRandomizer final : public Randomizer{
	public:
		void randomizeWorld(World& world) override;

	private:
		std::random_device rd;
		std::mt19937 generator{ rd() };
		std::uniform_int_distribution<> dist{ 0, 1 };
	};
}
