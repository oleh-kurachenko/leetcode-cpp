#include <vector>

#include <algorithm>
#include <array>
#include <climits>

/**
 * @note pre-optimization reference solution, no edge-dynamics, comparison and
 *       caching optimization
 */
class Solution {
  public:
    int maximumAmount(std::vector<std::vector<int>> &coins) {
        const size_t n = coins.size();
        const size_t m = coins[0].size();

        std::array<std::vector<std::vector<int>>, 3> dmap;

        for (auto &dmap_v : dmap) {
            dmap_v = std::vector(n, std::vector<int>(m));
        }

        dmap[2][0][0] = coins[0][0];
        dmap[1][0][0] = coins[0][0] >= 0 ? coins[0][0] : 0;
        dmap[0][0][0] = dmap[1][0][0];

        for (size_t i{1}; i < n; ++i) {
            dmap[2][i][0] = dmap[2][i - 1][0] + coins[i][0];
            dmap[1][i][0] =
                std::max(dmap[1][i - 1][0] + coins[i][0], dmap[2][i - 1][0]);
            dmap[0][i][0] =
                std::max(dmap[0][i - 1][0] + coins[i][0], dmap[1][i - 1][0]);
        }
        for (size_t j{1}; j < m; ++j) {
            dmap[2][0][j] = dmap[2][0][j - 1] + coins[0][j];
            dmap[1][0][j] =
                std::max(dmap[1][0][j - 1] + coins[0][j], dmap[2][0][j - 1]);
            dmap[0][0][j] =
                std::max(dmap[0][0][j - 1] + coins[0][j], dmap[1][0][j - 1]);
        }

        for (size_t i{1}; i < n; ++i) {
            for (size_t j{1}; j < m; ++j) {
                dmap[2][i][j] = std::max(dmap[2][i - 1][j], dmap[2][i][j - 1]) +
                                coins[i][j];
                dmap[1][i][j] = std::max({dmap[1][i - 1][j] + coins[i][j],
                    dmap[1][i][j - 1] + coins[i][j], dmap[2][i - 1][j],
                    dmap[2][i][j - 1]});
                dmap[0][i][j] = std::max({dmap[0][i - 1][j] + coins[i][j],
                    dmap[0][i][j - 1] + coins[i][j], dmap[1][i - 1][j],
                    dmap[1][i][j - 1]});
            }
        }

        return std::max({dmap[0][n - 1][m - 1], dmap[1][n - 1][m - 1],
            dmap[2][n - 1][m - 1]});
    }
};