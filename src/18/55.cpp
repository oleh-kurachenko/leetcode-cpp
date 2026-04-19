#include <vector>

class Solution {
  public:
    int maxDistance(
        const std::vector<int> &nums1, const std::vector<int> &nums2) {
        size_t i{0};
        size_t j{0};

        for (; i < nums1.size() && j < nums2.size(); ++j) {
            if (nums1[i] > nums2[j]) {
                ++i;
            }
        }

        if (j - i > 0) {
            return j - i - 1;
        }
        return 0;
    }
};