#include "roman_numeral_converter.hxx"
namespace w = workshop;

#include <gtest/gtest.h>
namespace t = testing;

#include <tuple>
namespace s = std;

class InvalidRomanNumeralFixture : public t::TestWithParam<char const*> {
};
class InvalidIntegerFixture : public t::TestWithParam<int> {
};

using ConversionParams = s::tuple<int, char const*>;
class RomanNumeralConversionFixture : public t::TestWithParam<ConversionParams> {
};

TEST_P(InvalidRomanNumeralFixture, throws_invalid_argument)
{
    ASSERT_THROW(w::from_roman(GetParam()), std::invalid_argument);
}

TEST_P(InvalidIntegerFixture, throws_invalid_argument)
{
    ASSERT_THROW(w::to_roman(GetParam()), std::invalid_argument);
}

TEST_P(RomanNumeralConversionFixture, converts_to_roman)
{
    // auto const& [value, roman] = GetParam();
    int value;
    std::string roman;
    std::tie(value, roman) = GetParam();

    ASSERT_EQ(w::to_roman(value), roman);
}

TEST_P(RomanNumeralConversionFixture, converts_from_roman)
{
    // auto const& [value, roman] = GetParam();
    int value;
    std::string roman;
    std::tie(value, roman) = GetParam();

    ASSERT_EQ(w::from_roman(roman), value);
}

INSTANTIATE_TEST_SUITE_P(
    RomanNumeralConverterTest,
    InvalidRomanNumeralFixture,
    t::Values("A", "ABC", "alpha", "mx", "23", "M!"));

INSTANTIATE_TEST_SUITE_P(
    RomanNumeralConverterTest,
    InvalidIntegerFixture,
    t::Values(0, 4000, 65536, -100));

constexpr auto cp(int const value, char const* const roman) { return ConversionParams { value, roman }; }
INSTANTIATE_TEST_SUITE_P(
    RomanNumeralConverterTest,
    RomanNumeralConversionFixture,
    t::Values(
        cp(1, "I"),
        cp(2, "II"),
        cp(4, "IV"),
        cp(5, "V"),
        cp(6, "VI"),
        cp(9, "IX"),
        cp(10, "X"),
        cp(11, "XI"),
        cp(12, "XII"),
        cp(14, "XIV"),
        cp(15, "XV"),
        cp(16, "XVI"),
        cp(23, "XXIII"),
        cp(49, "XLIX"),
        cp(50, "L"),
        cp(51, "LI"),
        cp(99, "XCIX"),
        cp(100, "C"),
        cp(101, "CI"),
        cp(149, "CXLIX"),
        cp(500, "D"),
        cp(999, "CMXCIX"),
        cp(1000, "M"),
        cp(1001, "MI"),
        cp(1400, "MCD"),
        cp(1500, "MD"),
        cp(1990, "MCMXC"),
        cp(3999, "MMMCMXCIX")));
