#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "../algorithms/abs_diff.cpp"

/**
 * @note close in performance, but not as fast as stable_sort
 */
class Solution {
  public:
    std::vector<long long> distance(const std::vector<int> &nums) {
        std::unordered_map<int, std::vector<unsigned>> index{};

        for (unsigned i{0}; i < nums.size(); ++i) {
            index[nums[i]].emplace_back(i);
        }

        std::vector<long long> distances(nums.size());

        for (const auto &[num, idxs] : index) {
            distances[idxs[0]] =
                std::accumulate(idxs.begin(), idxs.end(), 0ll) -
                idxs.size() * idxs[0];

            size_t left_count{0};
            size_t right_count{idxs.size() - 1};

            for (size_t i{1}; i < idxs.size(); ++i) {
                const long long delta{idxs[i] - idxs[i - 1]};

                --right_count;
                distances[idxs[i]] = distances[idxs[i - 1]] +
                                     delta * left_count - delta * right_count;
                ++left_count;
            }
        }

        return distances;
    }
};

int main() {
    std::vector nums{1, 3, 1, 1, 2};

    std::cout << Solution().distance(nums).size() << std::endl;
}