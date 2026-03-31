#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

#include <cstdint>
#include <limits>

class Solution {
  public:
    int maxProductPath(std::vector<std::vector<int>> &grid) {
        std::vector positive_max(
            grid.size(), std::vector<int64_t>(grid[0].size(), INVALID));
        std::vector negative_max(
            grid.size(), std::vector<int64_t>(grid[0].size(), INVALID));

        bool meet_zero{false};

        for (size_t i{0}; i < grid.size(); ++i) {
            for (size_t j{0}; j < grid[0].size(); ++j) {
                if (grid[i][j] == 0) {
                    meet_zero = true;
                }

                if (i == 0 && j == 0) {
                    positive_max[0][0] =
                        (grid[i][j] >= 0) ? grid[i][j] : INVALID;
                    negative_max[0][0] =
                        (grid[i][j] < 0) ? grid[i][j] : INVALID;

                    continue;
                }

                const int64_t top_positive =
                    (i > 0 && positive_max[i - 1][j] != INVALID)
                        ? positive_max[i - 1][j] * grid[i][j]
                        : INVALID;
                const int64_t left_positive =
                    (j > 0 && positive_max[i][j - 1] != INVALID)
                        ? positive_max[i][j - 1] * grid[i][j]
                        : INVALID;

                const int64_t top_negative =
                    (i > 0 && negative_max[i - 1][j] != INVALID)
                        ? negative_max[i - 1][j] * grid[i][j]
                        : INVALID;
                const int64_t left_negative =
                    (j > 0 && negative_max[i][j - 1] != INVALID)
                        ? negative_max[i][j - 1] * grid[i][j]
                        : INVALID;

                auto try_update = [&pos_max = positive_max[i][j],
                                      &neg_max = negative_max[i][j]](
                                      int64_t value) {
                    if (value != INVALID) {
                        if ((pos_max == INVALID && value >= 0) ||
                            (pos_max != INVALID && pos_max < value)) {
                            pos_max = value;
                        }
                        if ((neg_max == INVALID && value < 0) ||
                            (neg_max != INVALID && neg_max > value)) {
                            neg_max = value;
                        }
                    }
                };

                try_update(top_positive);
                try_update(left_positive);
                try_update(top_negative);
                try_update(left_negative);
            }
        }

        if (positive_max.back().back() == INVALID) {
            return (meet_zero) ? 0 : -1;
        }

        return static_cast<int>(positive_max.back().back() % MODULO);
    }

  private:
    static constexpr int MODULO{1'000'000'007};
    static constexpr int INVALID{std::numeric_limits<int>::max()};
};

int main() {
    std::vector<std::vector<int>> grid{{2}};
    std::cout << Solution().maxProductPath(grid) << std::endl;
}
