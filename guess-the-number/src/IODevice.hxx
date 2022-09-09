#pragma once

#include <string>

struct IODevice {
  virtual ~IODevice() noexcept = default;

  virtual std::string read_line() = 0;
  virtual bool read_int(int& n) = 0;
  virtual void print_line(std::string const& message) = 0;
};
