#pragma once

#include <Randomizer.hxx>

#include <gmock/gmock.h>

class MockRandomizer final : public gol::Randomizer {
public:
	MOCK_METHOD(void, randomizeWorld, (gol::World&), (override));
};
