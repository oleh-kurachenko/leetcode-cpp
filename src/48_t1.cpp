#include <iostream>
#include <vector>

/**
 * this variant is by far worse because of unsequential access to the memory
 */
class Solution {
private:
    void rotate_sequence(int &ref1, int &ref2, int &ref3, int &ref4) {
        const int tmp = ref1;
        ref1 = ref4;
        ref4 = ref3;
        ref3 = ref2;
        ref2 = tmp;
    }
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        const size_t n = matrix.size();

        for (size_t i{0}; i < n / 2; ++i) {
            for (size_t j{0}; j < (n + 1) / 2; ++j) {
                std::cerr << "i=" << i << " j=" << j << std::endl;
                rotate_sequence(matrix[i][j], matrix[j][n - i - 1], matrix[n - i - 1][n - j - 1], matrix[n - j - 1][i]);
            }
        }
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