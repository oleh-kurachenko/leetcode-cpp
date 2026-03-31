#include <iostream>
#include <ostream>
#include <vector>

#include <cstdint>
#include <numeric>
#include <unordered_map>

class Solution {
  public:
    bool canPartitionGrid(std::vector<std::vector<int>> &grid) {
        const size_t n = grid.size();
        const size_t m = grid[0].size();

        std::vector<uint64_t> rows(n, 0);
        std::vector<uint64_t> cols(m, 0);
        std::vector<uint16_t> values(VALUE_MAX + 1, 0);

        for (size_t i{0}; i < n; ++i) {
            for (size_t j{0}; j < m; ++j) {
                rows[i] += grid[i][j];
                cols[j] += grid[i][j];

                ++values[grid[i][j]];
            }
        }

        auto values2(values);
        if (canPartitionMatrixHorizontal<MatrixView<int>>(
                {grid}, values2, rows)) {
            return true;
        }

        return canPartitionMatrixHorizontal<MatrixDiagonalReflectionView<int>>(
            {grid}, values, cols);
    }

  private:
    static constexpr size_t VALUE_MAX{100'000};

    template <typename T> class MatrixView {
      public:
        MatrixView(std::vector<std::vector<T>> &data_ref) : _data{data_ref} {}

        T get(size_t i, size_t j) { return _data[i][j]; }

        size_t n() { return _data.size(); }

        size_t m() { return _data[0].size(); }

      private:
        std::vector<std::vector<T>> &_data;
    };

    template <typename T> class MatrixDiagonalReflectionView {
      public:
        MatrixDiagonalReflectionView(std::vector<std::vector<T>> &data_ref)
            : _data{data_ref} {}

        T get(size_t i, size_t j) { return _data[j][i]; }

        size_t n() { return _data[0].size(); }

        size_t m() { return _data.size(); }

      private:
        std::vector<std::vector<T>> &_data;
    };

    template <typename T>
    bool canPartitionMatrixHorizontal(T matrix_view,
        std::vector<uint16_t> &values, const std::vector<uint64_t> &rows) {
        std::unordered_map<int, uint16_t> top_risky;
        std::unordered_map<int, uint16_t> bottom_risky;

        top_risky.reserve(VALUE_MAX / 8);
        bottom_risky.reserve(VALUE_MAX / 8);

        for (size_t j{1}; j < matrix_view.m() - 1; ++j) {
            if (top_risky.count(matrix_view.get(0, j))) {
                ++top_risky[matrix_view.get(0, j)];
            } else {
                top_risky[matrix_view.get(0, j)] = 1;
            }

            if (bottom_risky.count(matrix_view.get(matrix_view.n() - 1, j))) {
                ++bottom_risky[matrix_view.get(matrix_view.n() - 1, j)];
            } else {
                bottom_risky[matrix_view.get(matrix_view.n() - 1, j)] = 1;
            }
        }

        std::vector<uint16_t> top_values(VALUE_MAX + 1, 0);
        for (size_t j{0}; j < matrix_view.m(); ++j) {
            ++top_values[matrix_view.get(0, j)];
            --values[matrix_view.get(0, j)];
        }

        uint64_t rows_sum = std::accumulate(rows.begin() + 1, rows.end(), 0llu);
        uint64_t rows_left_sum = rows.front();
        for (size_t i{1}; i < matrix_view.n(); ++i) {
            if (rows_left_sum == rows_sum) {
                return true;
            }

            int64_t difference = static_cast<int64_t>(rows_left_sum) - rows_sum;

            if (matrix_view.m() == 1) {
                if (i > 1 && (matrix_view.get(0, 0) == difference ||
                                 matrix_view.get(i - 1, 0) == difference)) {
                    return true;
                }
                if (i < matrix_view.n() - 1 &&
                    (matrix_view.get(i, 0) == -difference ||
                        matrix_view.get(matrix_view.n() - 1, 0) ==
                            -difference)) {
                    return true;
                }
            } else {
                std::vector<uint16_t> &values_ref =
                    (difference > 0) ? top_values : values;
                difference = std::abs(difference);

                if (difference <= VALUE_MAX) {
                    uint16_t risky_count{0};
                    if (i == 1 && top_risky.count(difference)) {
                        risky_count = top_risky[difference];
                    }
                    if (i == matrix_view.n() - 1 &&
                        bottom_risky.count(difference)) {
                        risky_count = bottom_risky[difference];
                    }

                    if (values_ref[difference] - risky_count > 0) {
                        return true;
                    }
                }
            }

            rows_left_sum += rows[i];
            rows_sum -= rows[i];
            for (size_t j{0}; j < matrix_view.m(); ++j) {
                ++top_values[matrix_view.get(i, j)];
                --values[matrix_view.get(i, j)];
            }
        }

        return false;
    }
};

int main() {
    std::vector<std::vector<int>> grid{{1, 2}, {3, 4}};

    std::cout << std::boolalpha << Solution().canPartitionGrid(grid)
              << std::endl;
}
