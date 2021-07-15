#pragma once

#include <gmock/gmock.h>

#include "RandomNumberGenerator.hxx"

struct MockRandomNumberGenerator final : RandomNumberGenerator {
	MOCK_METHOD(int, getNextNumber, (), (override));
	MOCK_METHOD(int, getMinValue, (), (const override));
	MOCK_METHOD(int, getMaxValue, (), (const override));
};

#include <utility>

constexpr bool operator == (
	RandomNumberGenerator const& lhs,
	RandomNumberGenerator const& rhs
	) {
	return std::addressof(lhs) == std::addressof(rhs);
}
