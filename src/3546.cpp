#include <iostream>
#include <ostream>
#include <vector>

#include <cstdint>
#include <numeric>

class Solution {
  public:
    bool canPartitionGrid(std::vector<std::vector<int>> &grid) {
        const size_t n = grid.size();
        const size_t m = grid[0].size();

        std::vector<uint64_t> rows(n, 0);
        std::vector<uint64_t> cols(m, 0);

        for (size_t i{0}; i < n; ++i) {
            for (size_t j{0}; j < m; ++j) {
                rows[i] += grid[i][j];
                cols[j] += grid[i][j];
            }
        }

        uint64_t rows_sum = std::accumulate(rows.begin() + 1, rows.end(), 0llu);
        uint64_t rows_left_sum = rows.front();
        for (size_t i{1}; i < n; ++i) {
            if (rows_left_sum == rows_sum) {
                return true;
            }
            rows_left_sum += rows[i];
            rows_sum -= rows[i];
        }

        uint64_t cols_sum = std::accumulate(cols.begin() + 1, cols.end(), 0llu);
        uint64_t cols_top_sum = cols.front();
        for (size_t i{1}; i < m; ++i) {
            if (cols_top_sum == cols_sum) {
                return true;
            }
            cols_top_sum += cols[i];
            cols_sum -= cols[i];
        }

        return false;
    }
};

int main() {
    std::vector<std::vector<int>> grid{{1, 4}, {2, 3}};

    std::cout << Solution().canPartitionGrid(grid) << std::endl;
}
