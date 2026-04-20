#include <cmath>

#include <limits>
#include <vector>

class Solution {
  public:
    int maxDistance(std::vector<int> &colors) {
        auto max_distance{std::numeric_limits<int>::min()};

        for (size_t i = 0; i < colors.size(); ++i) {
            for (size_t j = i + 1; j < colors.size(); ++j) {
                if (colors[i] != colors[j]) {
                    max_distance = std::max(max_distance,
                        std::abs(static_cast<int>(i) - static_cast<int>(j)));
                }
            }
        }

        return max_distance;
    }
};