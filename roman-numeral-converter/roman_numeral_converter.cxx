#include "roman_numeral_converter.hxx"

#include <array>
#include <iterator>
#include <regex>
#include <tuple>
#include <unordered_map>

namespace {
	using namespace std;

	array<tuple<string_view, int>, 13> const mapping{
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

	// IIFE - Immediatly Invoked Function Expression
	regex const ROMAN_NUMERAL_PATTERN = []() {
		string pattern{"^"};
		for (auto const[prefix, _] : mapping) {
			if (prefix.size() == 1) {
				pattern += prefix;
				pattern += "{0,3}";
			}
			else {
				pattern += "(?:";
				pattern += prefix;
				pattern += ")?";
			}
		}
		pattern += "$";
		return regex{ pattern };
	}();

	int prefixCount(string_view roman, string_view prefix) {
		if (prefix.size() == 1) {
			int count{ 0 };
			for (char const c : roman) {
				if (c == prefix[0] && count < 3)
					++count;
				else
					break;
			}
			return count;
		}
		else if (roman.substr(0, 2) == prefix) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int from_roman_faulty(string_view roman) {
		int result{ 0 };
		for (auto const[prefix, arabic] : mapping) {
			int const factor = prefixCount(roman, prefix);
			result += arabic * factor;
			roman.remove_prefix(factor * prefix.size());

			if (roman.empty())
				break;
		}

		if (!roman.empty() || result == 0) {
			throw invalid_argument{ "value is not a valid Roman numeral" };
		}

		return result;
	}

	int from_roman_with_regex(string_view roman) {
		if (!regex_match(begin(roman), end(roman), ROMAN_NUMERAL_PATTERN)) {
			throw invalid_argument{ "value is not a valid Roman numeral" };
		}

		return from_roman_faulty(roman);
	}

	int from_roman_with_reverse_mapping(std::string_view value) {
		// IIFE - Immediatly Invoked Function Expression
		static std::unordered_map<std::string, int> const reverse_mapping = []() {
			std::unordered_map<std::string, int> rmap;
			for (int n = 1; n <= 3999; ++n) {
				rmap[workshop::to_roman(n)] = n;
			}
			return rmap;
		}();

		auto const it = reverse_mapping.find(std::string{ value });
		if (it == reverse_mapping.end()) {
			throw std::invalid_argument{ "value is not a valid Roman numeral" };
		}

		return it->second;
	}
}

std::string workshop::to_roman(int value)
{
	if (value < 1 || value > 3999) {
		throw std::invalid_argument{ "value is not in the range of 1 to 3999" };
	}

	std::string result{};
	for (auto const[roman, arabic] : mapping) {
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
	return from_roman_with_reverse_mapping(value);
}
