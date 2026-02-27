#include <iostream>
#include <vector>

#include <algorithm>

class Solution {
public:
    /**
     * @note corrupting input data, but seems to be OK in those conditions
     */
    int minPathSum(std::vector<std::vector<int>>& grid) {
        for (size_t i{1}; i < grid.size(); ++i) {
            grid[i][0] += grid[i - 1][0];
        }
        for (size_t j{1}; j < grid[0].size(); ++j) {
            grid[0][j] += grid[0][j - 1];
        }
        for (size_t i{1}; i < grid.size(); ++i) {
            for (size_t j{1}; j < grid[0].size(); ++j) {
                grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);
            }
        }

        return grid[grid.size() - 1][grid[0].size() - 1];
    }
};

int main() {
    std::vector<std::vector<int>> map{};
    // map.push_back({1, 3, 1});
    // map.push_back({1, 5, 1});
    // map.push_back({4, 2, 1});

    map.push_back({1, 2, 3});
    map.push_back({4, 5, 6});

    std::cout << Solution().minPathSum(map) << std::endl;
}