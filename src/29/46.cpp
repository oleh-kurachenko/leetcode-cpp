#include <vector>

class Solution {
  public:
    bool areSimilar(std::vector<std::vector<int>> &mat, int k) {
        const size_t n{mat.size()};
        const size_t m{mat[0].size()};

        for (size_t i{0}; i < n; ++i) {
            for (size_t j{0}; j < m; ++j) {
                size_t j_k =
                    (i % 2) ? ((j + m) - (k % m)) % m : (j + (k % m)) % m;

                if (mat[i][j] != mat[i][j_k]) {
                    return false;
                }
            }
        }

        return true;
    }
};