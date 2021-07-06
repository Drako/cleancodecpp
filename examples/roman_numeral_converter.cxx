#include "roman_numeral_converter.hxx"

#include <algorithm>
#include <array>
#include <iterator>
#include <tuple>

namespace {
using namespace std;

array<tuple<string_view, int>, 13> const mapping {
    tuple { "M", 1000 },
    tuple { "CM", 900 },
    tuple { "D", 500 },
    tuple { "CD", 400 },
    tuple { "C", 100 },
    tuple { "XC", 90 },
    tuple { "L", 50 },
    tuple { "XL", 40 },
    tuple { "X", 10 },
    tuple { "IX", 9 },
    tuple { "V", 5 },
    tuple { "IV", 4 },
    tuple { "I", 1 },
};
}

std::string workshop::to_roman(int value)
{
    if (value < 1 || value > 3999) {
        throw std::invalid_argument { "value is not in the range of 1 to 3999" };
    }

    std::string result {};
    for (auto const [roman, arabic] : mapping) {
        while (value >= arabic) {
            value -= arabic;
            result += roman;
        }

        // early exit
        if (value == 0) {
            break;
        }
    }

    return result;
}

int workshop::from_roman(std::string_view const value)
{
    return 0;
}
