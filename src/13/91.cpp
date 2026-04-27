#include <vector>

class Solution {
  public:
    bool hasValidPath(const std::vector<std::vector<int>> &grid) {
        _n = grid.size();
        _m = grid[0].size();
        _grid = &grid;

        _visited = std::vector(_n, std::vector(_m, false));

        dfs(0, 0);

        return _visited[_n - 1][_m - 1];
    }

  private:
    size_t _n{};
    size_t _m{};

    const std::vector<std::vector<int>> *_grid{nullptr};
    std::vector<std::vector<bool>> _visited{};

    [[nodiscard]] auto &grid() const { return *_grid; }

    void dfs(size_t i_idx, size_t j_idx) {
        _visited[i_idx][j_idx] = true;
        const auto current_street = grid()[i_idx][j_idx];

        if (has_top_connection(current_street) && i_idx != 0 &&
            !_visited[i_idx - 1][j_idx]) {
            const auto next_street = grid()[i_idx - 1][j_idx];
            if (has_bottom_connection(next_street)) {
                dfs(i_idx - 1, j_idx);
            }
        }

        if (has_bottom_connection(current_street) && i_idx + 1 < _n &&
            !_visited[i_idx + 1][j_idx]) {
            const auto next_street = grid()[i_idx + 1][j_idx];
            if (has_top_connection(next_street)) {
                dfs(i_idx + 1, j_idx);
            }
        }

        if (has_left_connection(current_street) && j_idx != 0 &&
            !_visited[i_idx][j_idx - 1]) {
            const auto next_street = grid()[i_idx][j_idx - 1];
            if (has_right_connection(next_street)) {
                dfs(i_idx, j_idx - 1);
            }
        }

        if (has_right_connection(current_street) && j_idx + 1 < _m &&
            !_visited[i_idx][j_idx + 1]) {
            const auto next_street = grid()[i_idx][j_idx + 1];
            if (has_left_connection(next_street)) {
                dfs(i_idx, j_idx + 1);
            }
        }
    }

    static bool has_top_connection(const int street) {
        return street == 2 || street == 5 || street == 6;
    }

    static bool has_bottom_connection(const int street) {
        return street >= 2 && street <= 4;
    }

    static bool has_left_connection(const int street) {
        return street % 2 == 1;
    }

    static bool has_right_connection(const int street) {
        return street == 1 || street == 4 || street == 6;
    }
};