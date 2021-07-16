#pragma once

#include <UserInterface.hxx>

#include <gmock/gmock.h>

class MockUserInterface final : public gol::UserInterface {
public:
	MOCK_METHOD(void, renderWorld, (gol::World const&), (override));
	MOCK_METHOD(void, waitForUserInteraction, (), (override));
};
