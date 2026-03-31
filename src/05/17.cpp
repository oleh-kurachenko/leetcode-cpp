#include <iostream>
#include <vector>

#include <cstdint>
#include <numeric>

class Solution {
  public:
    int findMinMoves(std::vector<int> &machines) {
        const int32_t sum =
            std::accumulate(machines.begin(), machines.end(), 0, std::plus());
        if (sum % machines.size() != 0) {
            return -1;
        }

        const int32_t daily = sum / machines.size();
        int32_t daily_sum{0};
        int32_t real_sum{0};
        int32_t previous_delta{0};
        int32_t max_moves{0};

        for (const auto machine : machines) {
            daily_sum += daily;
            real_sum += machine;
            int32_t delta = daily_sum - real_sum;
            max_moves = std::max(max_moves, std::abs(delta));
            max_moves = std::max(max_moves, previous_delta - delta);
            previous_delta = delta;
        }

        return max_moves;
    }
};
