#include <cstdint>

#include <vector>

class Solution {
  public:
    int getMinDistance(std::vector<int> &nums, int target, int start) {
        const size_t ops_limit =
            std::max<size_t>(nums.size() - start, start + 1);

        for (size_t i{0}; i < ops_limit; ++i) {
            if (i + start < nums.size()) {
                if (nums[i + start] == target) {
                    return i;
                }
            }
            if (i <= start) {
                if (nums[start - i] == target) {
                    return i;
                }
            }
        }

        return -1; // guaranteed not to happen
    }
};
