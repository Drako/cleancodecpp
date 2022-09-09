#pragma once

#include "IODevice.hxx"

class Console final : public IODevice {
public:
  std::string read_line() override;
  bool read_int(int& n) override;
  void print_line(std::string const &message) override;
};
