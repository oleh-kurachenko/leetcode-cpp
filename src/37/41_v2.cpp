#include <vector>

#include <algorithm>
#include <cstdint>
#include <limits>

/**
 * @brief stable-sort-based solution, optimized in RAM-access
 */
class Solution {
  public:
    int minimumDistance(std::vector<int> &nums) {
        std::vector<NumIdx> idx(nums.size());

        for (size_t i{0}; i < idx.size(); ++i) {
            idx[i] = {nums[i], static_cast<uint32_t>(i)};
        }

        std::ranges::stable_sort(idx,
            [](const NumIdx v1, const NumIdx v2) { return v1.num < v2.num; });

        int min_distance{std::numeric_limits<int>::max()};

        for (size_t i{2}; i < idx.size(); ++i) {
            if (idx[i - 2].num == idx[i].num) {
                min_distance = std::min(min_distance,
                    static_cast<int>(idx[i].idx - idx[i - 2].idx));
            }
        }

        if (min_distance == std::numeric_limits<int>::max()) {
            return -1;
        }
        return 2 * min_distance;
    }

  private:
    struct NumIdx {
        int num;
        uint32_t idx;
    };
};
