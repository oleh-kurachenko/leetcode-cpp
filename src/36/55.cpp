#include <vector>

#include <cmath>
#include <cstdint>

#include "../algorithms/inverse_multiplier_modulo.cpp"

class Solution {
  public:
    int xorAfterQueries(
        std::vector<int> &nums, std::vector<std::vector<int>> &queries) {

        const size_t n{nums.size()};

        std::vector<std::vector<Query>> fast_queries(std::sqrt(n));

        for (const auto &query : queries) {
            const auto &l = query[0];
            const auto &r = query[1];
            const auto &k = query[2];
            const auto &v = query[3];

            if (k < fast_queries.size()) {
                fast_queries[k].push_back({l, r, v});
            } else {
                for (size_t j(l); j <= r; j += k) {
                    nums[j] = static_cast<int64_t>(nums[j]) * v % MOD;
                }
            }
        }

        std::vector<uint64_t> multipliers(n);
        for (size_t k{1}; k < fast_queries.size(); ++k) {
            const auto &fast_query = fast_queries[k];

            if (fast_query.empty()) {
                continue;
            }

            std::fill(multipliers.begin(), multipliers.end(), 1);

            for (const auto &query : fast_query) {
                multipliers[query.l] = multipliers[query.l] * query.v % MOD;
                if (const auto r = ((query.r - query.l) / k + 1) * k + query.l;
                    r < n) {
                    multipliers[r] =
                        multipliers[r] *
                        inverse_multiplier_modulo<uint64_t, MOD>(query.v) % MOD;
                }
            }

            for (size_t i{k}; i < n; ++i) {
                multipliers[i] = multipliers[i] * multipliers[i - k] % MOD;
            }
            for (size_t i{0}; i < n; ++i) {
                nums[i] = static_cast<uint64_t>(nums[i]) * multipliers[i] % MOD;
            }
        }

        int result{nums[0]};
        for (size_t i{1}; i < n; ++i) {
            result ^= nums[i];
        }

        return result;
    }

  private:
    static constexpr int MOD{1'000'000'007};

    struct Query {
        int l;
        int r;
        int v;
    };
};