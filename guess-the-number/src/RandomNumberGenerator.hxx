#pragma once

struct RandomNumberGenerator {
  virtual ~RandomNumberGenerator() noexcept = default;

  virtual int generate() = 0;
};
