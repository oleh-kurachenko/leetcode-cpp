#include <cassert>
#include <cstdint>

#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

/**
 * @note slightly inoptimal (there is a solution by far more simple), I was
 *       interested in tweaking hashmaps
 */
class Solution {
  public:
    int minMirrorPairDistance(const std::vector<int> &nums) {
        _reversed_cache.reserve(nums.size() * 2);
        _index.reserve(nums.size() * 2);

        build_index(nums);

        uint32_t min_distance{std::numeric_limits<uint32_t>::max()};
        for (size_t i{0}; i < nums.size(); ++i) {
            if (const auto index_itr = _index.find(nums[i]);
                index_itr != _index.end()) {

                const auto &indices = index_itr->second;
                if (indices.size() > 2) {
                    auto lower_bound = std::ranges::lower_bound(indices, i);
                    if (lower_bound != indices.begin()) {
                        if (*(lower_bound - 1) < i) {
                            min_distance = std::min<uint32_t>(
                                min_distance, i - *(lower_bound - 1));
                        }
                    }
                    if (lower_bound != indices.end() && *lower_bound == i) {
                        ++lower_bound;
                    }
                    if (lower_bound != indices.end()) {
                        if (*lower_bound < i) {
                        }
                        min_distance =
                            std::min<uint32_t>(min_distance, i - *lower_bound);
                    }
                    continue;
                }

                assert(!indices.empty());
                if (i != indices[0]) {
                    if (indices[0] < i) {
                        min_distance =
                            std::min<uint32_t>(min_distance, i - indices[0]);
                    }
                }
                if (indices.size() == 2 && i != indices[1]) {
                    if (indices[1] < i) {
                        min_distance =
                            std::min<uint32_t>(min_distance, i - indices[1]);
                    }
                }
            }
        }

        return min_distance;
    }

  private:
    using uint = uint64_t;

    std::unordered_map<uint, uint> _reversed_cache{};
    std::unordered_map<uint, std::vector<uint32_t>> _index{};

    uint get_reversed(const uint n) {
        if (!_reversed_cache.contains(n)) {
            uint reversed_n{0};
            uint copy_n{n};

            while (copy_n != 0) {
                reversed_n = reversed_n * 10 + copy_n % 10;
                copy_n = copy_n / 10;
            }
            _reversed_cache[n] = reversed_n;
        }

        return _reversed_cache[n];
    }

    void build_index(const std::vector<int> &nums) {
        for (size_t i{0}; i < nums.size(); ++i) {
            const auto reversed_n{get_reversed(nums[i])};

            _index[reversed_n].push_back(i);
        }
    }
};

int main() {
    std::vector nums{12, 21, 45, 33, 54};
    std::cout << Solution().minMirrorPairDistance(nums) << std::endl;
}
