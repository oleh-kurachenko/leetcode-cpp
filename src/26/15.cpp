#include <algorithm>
#include <vector>
#include <iostream>

#include "../algorithms/abs_diff.cpp"

class Solution {
  public:
    std::vector<long long> distance(const std::vector<int> &nums) {
        std::vector<std::pair<int, unsigned>> nums_indexed{}; // nums[i], i
        nums_indexed.reserve(nums.size());

        for (unsigned i{0}; i < nums.size(); ++i) {
            nums_indexed.emplace_back(nums[i], i);
        }
        std::ranges::stable_sort(nums_indexed,
            [](const auto v1, const auto v2) { return v1.first < v2.first; });

        std::vector<long long> distances(nums.size());

        size_t left_count{};
        size_t right_count{};
        for (size_t i{0}; i < nums_indexed.size(); ++i) {
            const auto num = nums_indexed[i].first;
            const auto idx = nums_indexed[i].second;

            long long nums_distance{0};

            if (i == 0 || nums_indexed[i - 1].first != num) {
                left_count = 0;
                right_count = 0;
                for (size_t j{i + 1};
                    j < nums.size() && num == nums_indexed[j].first; ++j) {

                    nums_distance += abs_diff(idx, nums_indexed[j].second);
                    ++right_count;
                }
            } else {
                const long long delta{idx - nums_indexed[i - 1].second};

                --right_count;
                nums_distance = distances[nums_indexed[i - 1].second] +
                    delta * left_count - delta * right_count;
                ++left_count;
            }

            distances[nums_indexed[i].second] = nums_distance;
        }

        return distances;
    }

    // problem 2121
    std::vector<long long> getDistances(const std::vector<int>& arr) {
        return distance(arr);
    }
};

int main() {
    std::vector nums{1, 3, 1, 1, 2};

    std::cout << Solution().distance(nums).size() << std::endl;
}