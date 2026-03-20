#include <vector>
#include <iostream>

#include <algorithm>
#include <limits>

class Solution {
public:
    std::vector<std::vector<int> > minAbsDiff(
        std::vector<std::vector<int> > &grid, int k) {
        const size_t grid_n{grid.size()};
        const size_t grid_m{grid[0].size()};

        std::vector<std::vector<int> > result(grid_n - k + 1);
        for (size_t i{0}; i < result.size(); ++i) {
            result[i].resize(grid_m - k + 1);
        }

        std::vector<int> buffer(k * k);
        for (size_t i{0}; i < result.size(); ++i) {
            for (size_t j{0}; j < result[0].size(); ++j) {
                for (size_t l{0}; l < k; ++l) {
                    std::copy_n(grid[i + l].begin() + j, k,
                                buffer.begin() + l * k);
                }

                std::sort(buffer.begin(), buffer.end());

                int result_here{std::numeric_limits<int>::max()};
                for (size_t l{1}; l < buffer.size(); ++l) {
                    if (buffer[l - 1] != buffer[l]) {
                        result_here = std::min(result_here,
                                               std::abs(
                                                   buffer[l - 1] - buffer[l]));
                    }
                }

                result[i][j] = result_here == std::numeric_limits<int>::max()
                                   ? 0
                                   : result_here;
            }
        }

        return result;
    }
};

int main() {
    std::vector<std::vector<int> > grid{{1, -2, 3}, {2, 3, 5}};
    std::cout << Solution().minAbsDiff(grid, 2)[0][0] << std::endl;
}
