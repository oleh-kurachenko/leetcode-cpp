#include <climits>
#include <cstdint>

#include <algorithm>
#include <ranges>
#include <vector>

#include <iostream>

class Solution {
  public:
    long long minimumTotalDistance(
        std::vector<int> &robot, std::vector<std::vector<int>> &factory) {

        _robots = std::move(robot);
        std::ranges::sort(_robots);

        std::ranges::sort(factory);

        for (auto factory_item : factory) {
            for (size_t i{0}; i < factory_item[1]; ++i) {
                _factories.push_back(factory_item[0]);
            }
        }

        _mtd_cache = std::vector(
            _robots.size(), std::vector(_factories.size(), LONG_LONG_MIN));

        return min_total_distance(0, 0);
    }

  private:
    std::vector<int> _robots;
    std::vector<int> _factories;
    std::vector<std::vector<long long>> _mtd_cache;

    long long min_total_distance(size_t robot_itr, size_t factory_itr) {
        if (robot_itr == _robots.size()) {
            return 0;
        }
        if (factory_itr == _factories.size()) {
            return LONG_LONG_MAX;
        }

        if (_mtd_cache[robot_itr][factory_itr] == LONG_LONG_MIN) {
            long long use_distance =
                min_total_distance(robot_itr + 1, factory_itr + 1);
            if (use_distance != LONG_LONG_MAX) {
                use_distance +=
                    std::abs(_robots[robot_itr] - _factories[factory_itr]);
            }

            _mtd_cache[robot_itr][factory_itr] =
                std::min(use_distance, min_total_distance(robot_itr, factory_itr + 1));
        }

        return _mtd_cache[robot_itr][factory_itr];
    }
};

int main() {
    std::vector<int> robots{9, 11, 99, 101};
    std::vector<std::vector<int>> factory{
        {10, 1}, {7, 1}, {14, 1}, {100, 1}, {96, 1}, {103, 1}};

    std::cout << Solution{}.minimumTotalDistance(robots, factory) << std::endl;
}