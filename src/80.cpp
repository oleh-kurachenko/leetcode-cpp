#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int> &nums) {
        size_t length{2};

        for (size_t i{2}; i < nums.size(); ++i) {
            if (nums[i] != nums[length - 2]) {
                nums[length++] = nums[i];
            }
        }

        return std::min(nums.size(), length);
    }
};

int main() {
    std::vector<int> nums{0, 0, 1, 1, 1, 1, 2, 3, 3};

    int new_length = Solution().removeDuplicates(nums);

    std::cout << new_length << std::endl;
    for (size_t i{0}; i < new_length; ++i) {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}
