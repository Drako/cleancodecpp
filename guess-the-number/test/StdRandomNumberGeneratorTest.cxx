#include <gtest/gtest.h>

#include <array>

#include "StdRandomNumberGenerator.hxx"

TEST(StdRandomNumberGeneratorTest, numbersShouldHaveEqualProbability)
{
  StdRandomNumberGenerator rng{};

  std::array<int, 100U> counts{};
  for (auto iterations{100'000U}; iterations--;) {
    auto const n = rng.generate();
    ASSERT_TRUE(n >= 1 && n <= 100);
    ++counts[static_cast<std::size_t>(n - 1)];
  }

  for (auto const n : counts) {
    EXPECT_TRUE(n >= 900 && n <= 1100);
  }
}
