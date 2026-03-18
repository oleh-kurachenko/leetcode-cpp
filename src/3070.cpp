#include <iostream>
#include <ostream>
#include <vector>

class Solution {
public:
    int countSubmatrices(std::vector<std::vector<int>>& grid, int k) {
        int result = grid[0][0] <= k ? 1 : 0;

        for (int i{1}; i < grid.size(); ++i) {
            grid[i][0] += grid[i - 1][0];
            if (grid[i][0] <= k) {
                ++result;
            }
        }
        for (int j{1}; j < grid[0].size(); ++j) {
            grid[0][j] += grid[0][j - 1];
            if (grid[0][j] <= k) {
                ++result;
            }
        }

        for (int i{1}; i < grid.size(); ++i) {
            for (int j{1}; j < grid[0].size(); ++j) {
                grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
                if (grid[i][j] <= k) {
                    ++result;
                }
            }
        }

        return result;
    }
};

int main() {
    std::vector<std::vector<int>> grid {{7, 2, 9}, {1, 5, 0},{2, 6, 6}};

    std::cout << Solution().countSubmatrices(grid, 20) << std::endl;
}
