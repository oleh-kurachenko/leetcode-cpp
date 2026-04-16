#include <cstdint>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<int> solveQueries(
        std::vector<int> &nums, std::vector<int> &queries) {

        build_index(nums);
        compute_distances(nums.size());

        for (size_t i{0}; i < queries.size(); ++i) {
            queries[i] = _distances[queries[i]];
        }

        return queries;
    }

  private:
    using sidx_t = int;

    std::unordered_map<int, std::vector<sidx_t>> _nums_index{};
    std::vector<int> _distances{};

    void build_index(const std::vector<int> &nums) {
        _nums_index.reserve(nums.size());

        for (size_t i{0}; i < nums.size(); ++i) {
            const int num{nums[i]};

            if (!_nums_index.contains(num)) {
                _nums_index.insert({num, {static_cast<sidx_t>(i)}});
            } else {
                _nums_index[num].push_back(i);
            }
        }
    }

    void compute_distances(const size_t nums_size) {
        _distances.resize(nums_size);

        for (const auto &index : _nums_index) {
            const auto idxs{index.second};

            if (idxs.size() == 1) {
                _distances[idxs[0]] = -1;
                continue;
            }

            for (size_t i{0}; i < idxs.size(); ++i) {
                const auto prev_idx =
                    (i > 0) ? idxs[i - 1] : idxs[idxs.size() - 1] - nums_size;
                const auto next_idx =
                    (i != idxs.size() - 1) ? idxs[i + 1] : idxs[0] + nums_size;

                _distances[idxs[i]] =
                    std::min(idxs[i] - prev_idx, next_idx - idxs[i]);
            }
        }
    }
};

int main() {
    std::vector<int> nums{1, 3, 1, 4, 1, 3, 2};
    std::vector<int> queries{0, 3, 5};

    std::cout << Solution{}.solveQueries(nums, queries).size() << std::endl;
}
