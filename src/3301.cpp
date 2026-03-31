#include <iostream>
#include <vector>

#include <algorithm>
#include <numeric>
#include <unordered_map>

class Solution {
  public:
    long long maximumTotalSum(std::vector<int> &maximumHeight) {

        std::sort(
            maximumHeight.begin(), maximumHeight.end(), std::greater<int>());

        long long sum{0};
        auto previous{std::numeric_limits<int>::max()};
        for (const auto max_height : maximumHeight) {
            previous = (max_height >= previous) ? previous - 1 : max_height;
            if (previous <= 0) {
                return -1;
            }
            sum += previous;
        }

        return sum;
    }
};

int main() {
    std::vector maximum_height{10, 23, 4, 2};
    std::cout << Solution().maximumTotalSum(maximum_height) << std::endl;
}
