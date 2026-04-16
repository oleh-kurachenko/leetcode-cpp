#include <cstdint>

#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * @brief hash table + binary search
 */
class Solution {
  public:
    std::vector<int> solveQueries(
        std::vector<int> &nums, std::vector<int> &queries) {

        build_index(nums);

        for (size_t i{0}; i < queries.size(); ++i) {
            queries[i] = query(nums, queries[i]);
        }

        return queries;
    }

  private:
    using sidx_t = int;

    std::unordered_map<int, std::vector<sidx_t>> _nums_index{};

    void build_index(const std::vector<int> &nums) {
        for (size_t i{0}; i < nums.size(); ++i) {
            const int num{nums[i]};
            const sidx_t idx{
                static_cast<sidx_t>(i) - static_cast<sidx_t>(nums.size())};

            if (!_nums_index.contains(num)) {
                _nums_index.insert({num, {idx}});
            } else {
                _nums_index[num].push_back(idx);
            }
        }
        for (size_t i{0}; i < nums.size(); ++i) {
            _nums_index[nums[i]].push_back(i);
        }
        for (size_t i{0}; i < nums.size(); ++i) {
            _nums_index[nums[i]].push_back(i + nums.size());
        }
    }

    int query(const std::vector<int> &nums, int idx) {
        const auto &index = _nums_index[nums[idx]];

        if (index.size() == 3) {
            return -1;
        }

        const auto lower_itr = std::ranges::lower_bound(index, idx);
        return std::min(idx - *(lower_itr - 1), *(lower_itr + 1) - idx);
    }
};
