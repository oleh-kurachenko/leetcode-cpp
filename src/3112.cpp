#include <iostream>
#include <ostream>

#include <vector>

class Solution {
public:
    int numberOfSubmatrices(std::vector<std::vector<char> > &grid) {
        std::vector<std::vector<int> > grid_diff(2);
        std::vector<bool> has_letters(grid[0].size(), false);
        int result{0};

        for (auto &row: grid_diff) {
            row.resize(grid[0].size());
        }

        has_letters[0] = (grid_diff[0][0] = delta(grid[0][0]));
        for (size_t j{1}; j < grid[0].size(); ++j) {
            has_letters[j] = has_letters[j] || has_letters[j - 1] || grid[0][j]
                             != '.';
            grid_diff[0][j] = grid_diff[0][j - 1] + delta(grid[0][j]);

            if (has_letters[j] && !grid_diff[0][j]) {
                ++result;
            }
        }

        for (size_t i{1}; i < grid.size(); ++i) {
            has_letters[0] = has_letters[0] || grid[i][0] != '.';
            grid_diff[i % 2][0] = grid_diff[(i - 1) % 2][0] + delta(grid[i][0]);

            if (has_letters[0] && !grid_diff[i % 2][0]) {
                ++result;
            }

            for (size_t j{1}; j < grid[i].size(); ++j) {
                has_letters[j] =
                        has_letters[j] || has_letters[j - 1] || grid[i][j] !=
                        '.';

                grid_diff[i % 2][j] =
                        grid_diff[(i - 1) % 2][j] + grid_diff[i % 2][j - 1] -
                        grid_diff[(i - 1) % 2][j - 1] + delta(grid[i][j]);

                if (has_letters[j] && !grid_diff[i % 2][j]) {
                    ++result;
                }
            }
        }

        return result;
    }

private:
    static int delta(const char c) {
        switch (c) {
            case 'X':
                return 1;
            case 'Y':
                return -1;
            default:
                return 0;
        }
    }
};

int main() {
    std::vector<std::vector<char> > grid{
        {'X', 'Y', '.'}, {
            'Y', '.',
            '.'
        }
    };
    std::cout << Solution().numberOfSubmatrices(grid) << std::endl;
}
