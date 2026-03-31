#include <string>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

class Solution {
  public:
    std::string generateString(std::string str1, std::string str2) {
        const auto n = str1.length();
        const auto m = str2.length();

        std::vector<bool> may_overlap(m);

        may_overlap[0] = true;
        for (size_t i{1}; i < may_overlap.size(); ++i) {
            may_overlap[i] =
                std::strncmp(str2.c_str(), str2.c_str() + i, m - i) == 0;
        }

        std::string result(n + m - 1, '\0');

        size_t previous_placement{SIZE_MAX};
        for (size_t i{n - 1}; i != SIZE_MAX; --i) {
            if (str1[i] == 'T') {
                if (previous_placement < i + m &&
                    !may_overlap[previous_placement - i]) {
                    return "";
                }
                for (size_t j{i}; j < previous_placement && j < i + m; ++j) {
                    result[j] = str2[j - i];
                }
                previous_placement = i;
            }
        }

        for (size_t i{0}; i < n; ++i) {
            if (str1[i] == 'F') {
                bool is_consistent{true};
                size_t last_empty{SIZE_MAX};

                for (size_t j{i + m - 1}; j >= i && j != SIZE_MAX; --j) {
                    char assumed = result[j] == '\0' ? 'a' : result[j];
                    if (assumed != str2[j - i]) {
                        is_consistent = false;
                    }
                    if (last_empty == SIZE_MAX && result[j] == '\0') {
                        last_empty = j;
                    }
                }
                if (!is_consistent) {
                    if (result[i] == '\0') {
                        result[i] = 'a';
                    }
                } else if (last_empty != -1) {
                    result[last_empty] = 'b';
                } else {
                    return "";
                }
            }
        }
        for (size_t i{0}; i < n + m - 1; ++i) {
            if (result[i] == '\0') {
                result[i] = 'a';
            }
        }

        return result;
    }
};

int main() {
    std::cout << Solution().generateString("FFTFFF", "a") << std::endl;
}
