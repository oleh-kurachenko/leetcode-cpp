#include <iostream>
#include <vector>

#include <algorithm>

class Solution {
private:
    void transpose(std::vector<std::vector<int>> &matrix) {
        for (size_t i{0}; i < matrix.size(); ++i) {
            for (size_t j{i + 1}; j < matrix[i].size(); ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        std::reverse(matrix.begin(), matrix.end());
        transpose(matrix);
    }
};

int main() {
    std::vector<std::vector<int>> matrix{};
    matrix.push_back({1, 2, 3, 4});
    matrix.push_back({5, 6, 7, 8});
    matrix.push_back({9, 10, 11, 12});
    matrix.push_back({13, 14, 15, 16});

    Solution().rotate(matrix);

    for (size_t i{0}; i < matrix.size(); ++i) {
        for (size_t j{0}; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}