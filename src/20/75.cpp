#include <iostream>
#include <string>

#include <vector>

class Solution {
  public:
    std::string decodeCiphertext(std::string encodedText, int rows) {
        if (encodedText.empty()) {
            return "";
        }

        std::vector<const char *> ptrs(rows);

        const size_t row_full_length{encodedText.length() / rows};
        const size_t row_length{row_full_length + 1 - rows};

        for (size_t i{0}; i < rows; ++i) {
            ptrs[i] = encodedText.c_str() + i * row_full_length + i;
        }

        std::string result;
        result.reserve(rows * row_length + rows * rows / 2 + 1);

        for (size_t j{0}; j < row_full_length; ++j) {
            for (size_t i{0};
                i < std::min(static_cast<size_t>(rows), row_full_length - j);
                ++i) {
                if (const char c{ptrs[i][j]}; c != '\0') {
                    result += c;
                }
            }
        }

        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        return result;
    }
};

int main() {
    std::cout << Solution().decodeCiphertext("iveo    eed   l te   olc", 4)
              << std::endl;
}