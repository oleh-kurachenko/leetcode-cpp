#include <iostream>
#include <ostream>
#include <vector>

#include <cstdint>
#include <numeric>

class Solution {
  public:
    std::vector<std::vector<int>> constructProductMatrix(
        std::vector<std::vector<int>> &grid) {
        const size_t n = grid.size();
        const size_t m = grid[0].size();

        std::vector<int> row_product(n);
        for (size_t i{0}; i < n; ++i) {
            row_product[i] = std::accumulate(
                grid[i].begin(), grid[i].end(), 1, multiplies_modulo);
        }

        std::vector<int> row_top_product(n);
        std::vector<int> row_bottom_product(n);
        row_top_product.front() = row_product.front();
        row_bottom_product.back() = row_product.back();

        for (size_t i{1}; i < n - 1; ++i) {
            row_top_product[i] =
                multiplies_modulo(row_top_product[i - 1], row_product[i]);
            row_bottom_product[n - i - 1] = multiplies_modulo(
                row_bottom_product[n - i], row_product[n - i - 1]);
        }

        std::vector<int> left_product(m);
        std::vector<int> right_product(m);

        for (size_t i{0}; i < n; ++i) {
            left_product.front() = grid[i].front();
            right_product.back() = grid[i].back();

            for (size_t j{1}; j < m - 1; ++j) {
                left_product[j] =
                    multiplies_modulo(left_product[j - 1], grid[i][j]);
                right_product[m - j - 1] =
                    multiplies_modulo(right_product[m - j], grid[i][m - j - 1]);
            }

            for (size_t j{0}; j < m; ++j) {
                int result{1};

                if (i > 0) {
                    result = multiplies_modulo(result, row_top_product[i - 1]);
                }
                if (i < n - 1) {
                    result =
                        multiplies_modulo(result, row_bottom_product[i + 1]);
                }
                if (j > 0) {
                    result = multiplies_modulo(result, left_product[j - 1]);
                }
                if (j < m - 1) {
                    result = multiplies_modulo(result, right_product[j + 1]);
                }

                grid[i][j] = result;
            }
        }

        return grid;
    }

  private:
    static constexpr int MODULO{12345};

    static int multiplies_modulo(const int v1, const int v2) {
        return static_cast<int>(static_cast<int64_t>(v1) * v2 % MODULO);
    }
};

int main() {
    std::vector<std::vector<int>> grid{{2, 7, 2, 6}};

    auto res = Solution().constructProductMatrix(grid);

    std::cout << res[0][0] << std::endl;
}
