#include <vector>

#include <algorithm>
#include <array>
#include <climits>

class Solution {
  public:
    int maximumAmount(std::vector<std::vector<int>> &coins) {
        const size_t n = coins.size();
        const size_t m = coins[0].size();

        // indexing: [m][r], where r - remaining neutralizations
        // using 4 instead of 3 improves caching
        std::vector<std::array<int, 4>> dmap(m);

        dmap[0][2] = coins[0][0];
        dmap[0][1] = coins[0][0] >= 0 ? coins[0][0] : 0;
        dmap[0][0] = dmap[0][1];

        for (size_t j{1}; j < m; ++j) {
            int coin{coins[0][j]};
            dmap[j][2] = dmap[j - 1][2] + coin;
            dmap[j][1] = std::max(dmap[j - 1][1] + coin, dmap[j - 1][2]);
            dmap[j][0] = std::max(dmap[j - 1][0] + coin, dmap[j - 1][1]);
        }

        for (size_t i{1}; i < n; ++i) {
            int coin{coins[i][0]};
            std::array<int, 4> prev{dmap[0]};

            dmap[0][2] = prev[2] + coin;
            dmap[0][1] = std::max(prev[1] + coin, prev[2]);
            dmap[0][0] = std::max(prev[0] + coin, prev[1]);

            for (size_t j{1}; j < m; ++j) {
                coin = coins[i][j];
                prev = dmap[j];

                const int tmp_max_2 = std::max(prev[2], dmap[j - 1][2]);
                dmap[j][2] = tmp_max_2 + coin;
                const int tmp_max_1 = std::max(prev[1], dmap[j - 1][1]);
                dmap[j][1] = std::max(tmp_max_1 + coin, tmp_max_2);
                dmap[j][0] = std::max(
                    std::max(prev[0], dmap[j - 1][0]) + coin, tmp_max_1);
            }
        }

        return dmap.back()[0];
    }
};
