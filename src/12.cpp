#include <iostream>
#include <string>

#include <algorithm>
#include <cassert>
#include <vector>
#include <cstdint>
#include <array>
#include <sstream>

class Solution {
private:
    static constexpr size_t N{4};

    struct DigitGroup {
        char ONE;
        char FIVE;
    };

    static constexpr std::array<DigitGroup, N> ROMAN_DIGITS{
        DigitGroup{'M', '_'}, DigitGroup{'C', 'D'}, DigitGroup{'X', 'L'},
        DigitGroup{'I', 'V'}
    };

    std::array<std::uint8_t, N> toNDigits(int number) {
        std::array<std::uint8_t, N> digits{};

        for (size_t i{0}; i < N; ++i) {
            digits[i] = number % 10;
            number /= 10;
        }

        std::reverse(digits.begin(), digits.end());
        return digits;
    }

public:
    std::string intToRoman(int num) {
        assert(num >= 0 && num <= 3999);

        std::ostringstream os;

        const auto digits = toNDigits(num);
        for (size_t i{0}; i < digits.size(); ++i) {
            auto digit = digits[i];

            if (digit == 0) {
                continue;
            }
            if (digit == 9) {
                os << ROMAN_DIGITS[i].ONE << ROMAN_DIGITS[i - 1].ONE;
                continue;
            }
            if (digit == 4) {
                os << ROMAN_DIGITS[i].ONE << ROMAN_DIGITS[i].FIVE;
                continue;
            }
            if (digit > 4) {
                os << ROMAN_DIGITS[i].FIVE;
                digit -= 5;
            }
            for (size_t j{0}; j < digit; ++j) {
                os << ROMAN_DIGITS[i].ONE;
            }
        }

        return os.str();
    }
};

int main() {
    std::cout << Solution().intToRoman(3999) << std::endl;
}
