#include <iostream>
#include <vector>

#include <cassert>
#include <climits>
#include <cmath>

/**
 * @note tried for daily challange, on optimal - should aim for single point
 *       search instead of current+previous
 */
class Solution {
  private:
    static constexpr long long MAX_SECONDS{LONG_LONG_MAX};

    long long countHeight(
        long long seconds, const std::vector<int> &workerTimes) {
        long long result{0};

        for (const auto v : workerTimes) {
            result += std::floor((std::sqrt(8. * seconds / v + 1) - 1) / 2);
        }

        return result;
    }

  public:
    long long minNumberOfSeconds(
        int mountainHeight, std::vector<int> &workerTimes) {
        long long current_seconds{MAX_SECONDS / 2};
        long long current_binary_step{MAX_SECONDS / 2};

        while (true) {
            const auto current_height =
                countHeight(current_seconds, workerTimes);
            const auto previous_height =
                countHeight(current_seconds - 1, workerTimes);

            if (current_height >= mountainHeight &&
                previous_height < mountainHeight) {
                return current_seconds;
            }

            current_binary_step = std::max(current_binary_step / 2, 1ll);
            if (current_height < mountainHeight) {
                current_seconds += current_binary_step;
            } else {
                current_seconds -= current_binary_step;
            }
        }

        assert(false);
    }
};

int main() {
    std::vector<int> workerTimes{1000000};
    std::cout << Solution().minNumberOfSeconds(100000, workerTimes)
              << std::endl;
}