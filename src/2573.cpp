#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include <cassert>
#include <cstdint>
#include <limits>

class Solution {
  public:
    std::string findTheString(std::vector<std::vector<int>> &lcp) {
        const size_t n = lcp.size();

        for (size_t i{0}; i < n; ++i) {
            if (lcp[i][i] != n - i) {
                return "";
            }
            for (size_t j{i + 1}; j < n; ++j) {
                if (lcp[i][j] != lcp[j][i]) {
                    return "";
                }
            }
        }

        assert(
            n < static_cast<decltype(n)>(std::numeric_limits<uint16_t>::max()));

        std::vector<uint16_t> order(n);
        for (size_t i{0}; i < n; ++i) {
            order[i] = i;
        }

        for (size_t i{0}; i < n; ++i) {
            for (size_t j{i + 1}; j < n; ++j) {
                if (lcp[i][j]) {
                    if (order[j] < i && order[j] != order[i]) {
                        return "";
                    }
                    if (order[i] == i) {
                        order[j] = i;
                    }
                    if (order[j] != order[i]) {
                        return "";
                    }
                }

                int previous{0};
                if (i < n - 1 && j < n - 1) {
                    previous = lcp[i + 1][j + 1];
                }

                if (lcp[i][j] != previous + 1 && lcp[i][j] != 0) {
                    return "";
                }
            }
        }

        char next_char{'a'};
        std::string s(n, ' ');
        for (size_t i{0}; i < n; ++i) {
            if (order[i] == i) {
                if (next_char > 'z') {
                    return "";
                }
                s[i] = next_char;
                ++next_char;
            } else {
                s[i] = s[order[i]];
            }
        }

        return s;
    }
};

int main() {
    // clang-format off
    std::vector<std::vector<int>> lcp{
            {4, 3, 2, 1},
            {3, 3, 2, 1},
            {2, 2, 2, 1},
            {1, 1, 1, 1}
    };
    // clang-format on

    std::cout << Solution().findTheString(lcp) << std::endl;
}