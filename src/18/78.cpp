#include <set>
#include <vector>

class Solution {
  public:
    std::vector<int> getBiggestThree(std::vector<std::vector<int>> &grid) {
        auto r_diagonal_sum = grid;
        auto l_diagonal_sum = grid;

        for (size_t i{0}; i < grid.size(); ++i) {
            for (size_t j{0}; j < grid[0].size(); ++j) {
                if (i > 0 && j > 0) {
                    r_diagonal_sum[i][j] += r_diagonal_sum[i - 1][j - 1];
                }
                if (i > 0 && j < grid[0].size() - 1) {
                    l_diagonal_sum[i][j] += l_diagonal_sum[i - 1][j + 1];
                }
            }
        }

        std::set<int> result;

        for (size_t i{0}; i < grid.size(); ++i) {
            for (size_t j{0}; j < grid[0].size(); ++j) {
                for (size_t k{0};
                    i >= k && i + k < grid.size() && j + 2 * k < grid[0].size();
                    ++k) {
                    int sum = grid[i - k][j + k];

                    if (k) {
                        sum +=
                            l_diagonal_sum[i][j] - l_diagonal_sum[i - k][j + k];
                        sum += r_diagonal_sum[i][j + 2 * k] -
                               r_diagonal_sum[i - k][j + k];
                        sum +=
                            r_diagonal_sum[i + k][j + k] - r_diagonal_sum[i][j];
                        sum += l_diagonal_sum[i + k][j + k] -
                               l_diagonal_sum[i][j + 2 * k];
                        sum -= grid[i + k][j + k];
                    }

                    if (result.size() < RESULTS_COUNT ||
                        sum > *result.begin()) {
                        result.insert(sum);
                        if (result.size() > RESULTS_COUNT) {
                            result.erase(result.begin());
                        }
                    }
                }
            }
        }

        return {result.rbegin(), result.rend()};
    }

  private:
    static constexpr size_t RESULTS_COUNT{3};
};

int main() {
    std::vector v{std::vector{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    auto t = Solution().getBiggestThree(v);
}
