#include <array>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

class Solution {
  public:
    bool containsCycle(const std::vector<std::vector<char>> &grid) {
        _n = grid.size();
        _m = grid[0].size();
        _grid = &grid;
        _visited = std::vector(_n, std::vector(_m, false));

        for (size_t i{0}; i < _n; ++i) {
            for (size_t j{0}; j < _m; ++j) {
                if (!_visited[i][j]) {
                    if (dfs_find_cycle({i, j}, {})) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

  private:
    struct Point {
        Point() : x(VALUE_MAX), y(VALUE_MAX) {}

        Point(size_t x, size_t y) : x(x), y(y) {}

        operator bool() const { return x != VALUE_MAX && y != VALUE_MAX; }

        bool operator==(const Point &p) const { return x == p.x && y == p.y; }

        size_t x;
        size_t y;

        static constexpr size_t VALUE_MAX{std::numeric_limits<size_t>::max()};
    };

    size_t _n{};
    size_t _m{};
    const std::vector<std::vector<char>> *_grid{nullptr};
    std::vector<std::vector<bool>> _visited{};

    bool dfs_find_cycle(const Point p, const Point previous) {
        const auto &grid = *_grid;
        const auto p_value = grid[p.x][p.y];

        _visited[p.x][p.y] = true;

        const std::array lookup{Point{p.x - 1, p.y}, Point{p.x + 1, p.y},
            Point{p.x, p.y - 1}, Point{p.x, p.y + 1}};

        for (const auto next : lookup) {
            if (next.x != Point::VALUE_MAX && next.y != Point::VALUE_MAX &&
                next.x != _n && next.y != _m &&
                grid[next.x][next.y] == p_value) {

                if (_visited[next.x][next.y]) {
                    if (previous && next != previous) {
                        return true;
                    }
                } else {
                    if (dfs_find_cycle(next, p)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    std::cout << Solution().containsCycle(
                     {{'a', 'a', 'a', 'a'}, {'a', 'b', 'b', 'a'},
                         {'a', 'b', 'b', 'a'}, {'a', 'a', 'a', 'a'}})
              << std::endl;
}
