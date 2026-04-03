#include <vector>

#include <algorithm>
#include <climits>
#include <queue>

class Solution {
  public:
    int maxWalls(std::vector<int> &robots, std::vector<int> &distance,
        std::vector<int> &walls) {

        std::vector<Robot> robs;
        robs.reserve(robots.size());

        for (size_t i{0}; i < robots.size(); ++i) {
            robs.emplace_back(robots[i], distance[i]);
        }

        std::ranges::sort(
            robs, [](const Robot &v1, const Robot &v2) { return v1.x < v2.x; });
        std::ranges::sort(walls);

        int left_lower_idx{0};
        int right_upper_idx{0};
        int right_lower_idx{0};
        std::queue<int> right_lower_idx_queue;

        int prev_right_count{0};
        int left_total{0};
        int right_total{0};

        for (size_t i{0}; i < robs.size(); ++i) {
            while (right_lower_idx < walls.size() &&
                   walls[right_lower_idx] < robs[i].x) {
                ++right_lower_idx;
            }
            right_lower_idx_queue.push(right_lower_idx);

            right_upper_idx = right_lower_idx;
            while (right_upper_idx < walls.size() &&
                   walls[right_upper_idx] <= robs[i].x) {
                ++right_upper_idx;
                   }
            const int left_upper_idx{right_upper_idx};

            int left_distance_limit = robs[i].x - robs[i].dist;
            if (i > 0) {
                left_distance_limit =
                    std::max(left_distance_limit, robs[i - 1].x + 1);
            }
            while (left_lower_idx < walls.size() &&
                   walls[left_lower_idx] < left_distance_limit) {
                ++left_lower_idx;
            }
            int left_count = left_upper_idx - left_lower_idx;

            int right_distance_limit = robs[i].x + robs[i].dist;
            if (i < robs.size() - 1) {
                right_distance_limit =
                    std::min(right_distance_limit, robs[i + 1].x - 1);
            }
            while (right_upper_idx < walls.size() &&
                   walls[right_upper_idx] <= right_distance_limit) {
                ++right_upper_idx;
            }
            int right_count = right_upper_idx - right_lower_idx;

            if (right_lower_idx_queue.size() > 1) {
                int prev_right_lower_idx = right_lower_idx_queue.front();
                right_lower_idx_queue.pop();

                const int prev_left_total{left_total};
                const int prev_right_total{right_total};

                left_total = std::max(prev_left_total + left_count,
                    prev_right_total - prev_right_count +
                        std::min(left_count + prev_right_count,
                            left_upper_idx - prev_right_lower_idx));
                right_total = std::max(prev_left_total + right_count,
                    prev_right_total + right_count);
            } else {
                left_total = left_count;
                right_total = right_count;
            }

            prev_right_count = right_count;
        }

        return std::max(left_total, right_total);
    }

  private:
    struct Robot {
        int x;
        int dist;
    };
};