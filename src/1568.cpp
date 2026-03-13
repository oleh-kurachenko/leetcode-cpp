#include <vector>
#include <iostream>

#include <algorithm>
#include <limits>
#include <numeric>

class Solution {
private:
    size_t n{0};
    size_t m{0};

    int timer{1};
    int min_connections{2};

    const size_t S_MAX{std::numeric_limits<size_t>::max()};

    void dfs(std::vector<std::vector<int> > &grid,
             std::vector<std::vector<int> > &f_up_grid, size_t x, size_t y,
             size_t x_prev, size_t y_prev) {
        size_t connections_count{0};

        ++timer;
        grid[x][y] = timer;
        f_up_grid[x][y] = timer;

        auto process_node = [&](size_t next_x, size_t next_y) {
            if (grid[next_x][next_y] == 1) {
                dfs(grid, f_up_grid, next_x, next_y, x, y);
                f_up_grid[x][y] =
                        std::min(f_up_grid[x][y], f_up_grid[next_x][next_y]);
                if (f_up_grid[next_x][next_y] >= grid[x][y] && x_prev != S_MAX) {
                    min_connections = 1;
                }
                ++connections_count;
            } else {
                f_up_grid[x][y] = std::min(f_up_grid[x][y], grid[next_x][next_y]);
            }
        };

        if (x > 0 && grid[x - 1][y] > 0 && (x != x_prev || y != y_prev)) {
            process_node(x - 1, y);
        }

        if (y > 0 && grid[x][y - 1] > 0 && (y != y_prev || x != x_prev)) {
            process_node(x, y - 1);
        }

        if (x + 1 < n && grid[x + 1][y] > 0 && (x != x_prev || y != y_prev)) {
            process_node(x + 1, y);
        }

        if (y + 1 < m && grid[x][y + 1] > 0 && (y != y_prev || x != x_prev)) {
            process_node(x, y + 1);
        }

        if (x_prev == S_MAX && connections_count > 1) {
            min_connections = 1;
        }
    }

public:
    int minDays(std::vector<std::vector<int> > &grid) {
        n = grid.size();
        m = grid[0].size();

        if (n * m <= 2) {
            return std::accumulate(grid.begin(), grid.end(), 0,
                                   [](int sum, const std::vector<int> &line) {
                                       return sum + std::accumulate(
                                                  line.begin(), line.end(), 0);
                                   });
        }

        bool found_first{false};
        std::vector f_up_grid(n, std::vector(m, 0));

        for (size_t i{0}; i < n; ++i) {
            for (size_t j{0}; j < m; ++j) {
                if (grid[i][j] == 1) {
                    if (found_first) {
                        return 0;
                    }
                    found_first = true;

                    grid[i][j] = 2;
                    dfs(grid, f_up_grid, i, j,
                        S_MAX,
                        S_MAX);
                }
            }
        }

        if (!found_first) {
            return 0;
        }

        if (timer == 2) {
            return 1;
        }

        return min_connections;
    }
};

int main() {
    std::vector<std::vector<int> > grid{
        {0,0,0},{0,1,0},{0,0,0}
    };

    std::cout << Solution().minDays(grid) << std::endl;
}
