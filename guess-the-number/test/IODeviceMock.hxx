#pragma once

#include "IODevice.hxx"

#include <gmock/gmock.h>

class IODeviceMock final: public IODevice
{
public:
  MOCK_METHOD(std::string, read_line, (), (override));
  MOCK_METHOD(bool, read_int, (int& n), (override));
  MOCK_METHOD(void, print_line, (std::string const&), (override));
};
