#include <vector>

#include <cstdint>

class Solution {
  public:
    int xorAfterQueries(
        std::vector<int> &nums, std::vector<std::vector<int>> &queries) {
        for (const auto &query : queries) {
            for (size_t j(query[0]); j <= query[1]; j += query[2]) {
                nums[j] = static_cast<int64_t>(nums[j]) * query[3] % MOD;
            }
        }

        int result{nums[0]};
        for (size_t i(1); i < nums.size(); i++) {
            result ^= nums[i];
        }

        return result;
    }

  private:
    static constexpr int MOD{1'000'000'007};
};