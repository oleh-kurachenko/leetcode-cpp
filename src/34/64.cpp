#include <cstdint>

#include <algorithm>
#include <limits>
#include <vector>

class Solution {
  public:
    int maxDistance(const int side, const std::vector<std::vector<int>> &points, int k) {
        _side = side;
        _k = k;

        fill_points(points);

        std::ranges::sort(_points);

        int result{0};
        uint_t low {1};
        uint_t high {this->side()};

        while (low <= high) {
            if (const uint_t middle = (low + high) / 2; check(middle)) {
                low = middle + 1;
                result = middle;
            } else {
                high = middle - 1;
            }
        }

        return result;
    }

  private:
    using uint_t = uint32_t;

    int _side{};
    std::vector<uint_t> _points{};
    int _k{};

    [[nodiscard]] uint_t side() const {
        return _side;
    }

    void fill_points(const std::vector<std::vector<int>> &points) {
        _points.reserve(points.size());

        for (const auto &point : points) {
            const auto &x = point[0];
            const auto &y = point[1];

            if (x == 0) {
                _points.push_back(y);
            } else if (y == _side) {
                _points.push_back(side() + x);
            } else if (x == _side) {
                _points.push_back(3 * side() - y);
            } else {
                _points.push_back(4 * side() - x);
            }
        }
    }

    bool check(const uint_t limit) {
        for (const auto start : _points) {
            const auto end = start + 4 * side() - limit;
            auto current = start;

            for (int i{0}; i < _k - 1; ++i) {
                auto itr = std::ranges::lower_bound(_points, current + limit);

                if (itr == _points.end() || *itr > end) {
                    current = std::numeric_limits<uint_t>::max();
                    break;
                }
                current = *itr;
            }

            if (current != std::numeric_limits<uint_t>::max()) {
                return true;
            }
        }

        return false;
    }
};