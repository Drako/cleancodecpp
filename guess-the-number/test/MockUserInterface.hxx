#pragma once

#include <gmock/gmock.h>

#include "UserInterface.hxx"

struct MockUserInterface final : UserInterface {
	MOCK_METHOD(int, requestGuess, (int), (override));
	MOCK_METHOD(bool, keepRunning, (), (override));
	MOCK_METHOD(void, showIntro, (RandomNumberGenerator const&), (override));
	MOCK_METHOD(void, showResult, (int, int, CheckResult), (override));
};
