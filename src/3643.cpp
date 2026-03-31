#include <vector>

#include <algorithm>

/**
 * @note how fun would it be with SIMD
 */
class Solution {
  public:
    std::vector<std::vector<int>> reverseSubmatrix(
        std::vector<std::vector<int>> &grid, int x, int y, int k) {
        std::vector<int> tmp(k);

        for (size_t i = 0; i < k / 2; ++i) {
            std::copy_n(grid[x + i].begin() + y, k, tmp.begin());
            std::copy_n(
                grid[x + k - i - 1].begin() + y, k, grid[x + i].begin() + y);
            std::copy_n(tmp.begin(), k, grid[x + k - i - 1].begin() + y);
        }

        return grid;
    }
};
