#include <vector>

class Solution {
  public:
    bool findRotation(std::vector<std::vector<int>> &mat,
        std::vector<std::vector<int>> &target) {
        const size_t n = mat.size();

        bool eq_nrt{true};
        bool eq_90deg{true};
        bool eq_180deg{true};
        bool eq_270deg{true};

        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < n; ++j) {
                if (mat[i][j] != target[i][j]) {
                    eq_nrt = false;
                }
                if (mat[i][j] != target[j][n - i - 1]) {
                    eq_90deg = false;
                }
                if (mat[i][j] != target[n - i - 1][n - j - 1]) {
                    eq_180deg = false;
                }
                if (mat[i][j] != target[n - j - 1][i]) {
                    eq_270deg = false;
                }
            }
        }

        return eq_nrt || eq_90deg || eq_180deg || eq_270deg;
    }
};
