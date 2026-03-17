#include <algorithm>
#include <vector>

class Solution {
public:
    int largestSubmatrix(std::vector<std::vector<int>>& matrix) {
        for (size_t i{1}; i < matrix.size(); i++) {
            for (size_t j{0}; j < matrix[0].size(); j++) {
                if (matrix[i][j] != 0) {
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
        }

        for (size_t i{0}; i < matrix.size(); i++) {
            std::sort(matrix[i].begin(), matrix[i].end());
        }

        int result{0};

        for (size_t i{0}; i < matrix.size(); i++) {
            for (size_t j{0}; j < matrix[0].size(); j++) {
                const int submatrix_size = matrix[i][j] * (matrix[i].size() - j);
                result = std::max(result, submatrix_size);
            }
        }

        return result;
    }
};
