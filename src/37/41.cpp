#include <climits>
#include <cstdint>
#include <cstring>

#include <array>
#include <bit>
#include <iostream>
#include <limits>
#include <vector>

#if PROBLEM_ID == 3741
using uint_t = uint32_t;
using uint_double_t = uint64_t;
constexpr uint_t N_MAX{100'001};
#elif PROBLEM_ID == 3740
using uint_t = uint8_t;
using uint_double_t = uint16_t;
constexpr uint_t N_MAX{101};
#endif

static_assert(2 * sizeof(uint_t) == sizeof(uint_double_t));

/**
 * @brief index-hash-based solution, RAM-usage optimized
 */
class Solution {
  public:
    int minimumDistance(std::vector<int> &nums) {
        std::array<UIntPair, N_MAX> idx{};
        std::memset(idx.data(), UINT8_MAX, N_MAX * sizeof(UIntPair));

        uint_t min_distance{std::numeric_limits<uint_t>::max()};

        for (uint_t i{0}; i < nums.size(); ++i) {
            auto &idxn = idx[nums[i]];

            if (idxn.u._0 == std::numeric_limits<uint_t>::max()) {
                idxn.u._0 = i;
            } else if (idxn.u._1 == std::numeric_limits<uint_t>::max()) {
                idxn.u._1 = i;
            } else {
                if (const auto diff{i - idxn.u._0}; diff < min_distance) {
                    min_distance = diff;
                }
                idxn.ud = idxn.ud << std::numeric_limits<uint_t>::digits | i;
            }
        }

        if (min_distance == std::numeric_limits<uint_t>::max()) {
            return -1;
        }
        return 2 * min_distance;
    }

  private:
    static_assert(std::endian::native == std::endian::little);

    union UIntPair {
        uint_double_t ud;
        struct {
            uint_t _1;
            uint_t _0;
        } u;
    };
};

int main() {
    std::vector nums{5, 3, 5, 5, 5};

    std::cout << Solution().minimumDistance(nums) << std::endl;
}