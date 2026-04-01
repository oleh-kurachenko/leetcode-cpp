#include <string>
#include <vector>

#include <algorithm>
#include <array>
#include <climits>

/**
 * @note initial O(n^2) solution, lacks proper mathematical analysis
 */
class Solution {
  public:
    std::vector<int> survivedRobotsHealths(std::vector<int> &positions,
        std::vector<int> &healths, std::string directions) {

        std::array<std::vector<Robot>, 2> robots;
        for (auto &v : robots) {
            v.reserve(positions.size());
        }

        for (size_t i{0}; i < positions.size(); ++i) {
            robots[0].emplace_back(
                positions[i], healths[i], directions[i] == 'L', i);
        }

        std::sort(robots[0].begin(), robots[0].end(),
            [](const Robot &v1, const Robot &v2) {
                return v1.position < v2.position;
            });

        size_t r{0};
        for (;; r = (r + 1) % 2) {
            auto &curr_robots = robots[r];
            auto &next_robots = robots[(r + 1) % 2];

            int next_collision_in{INT_MAX};
            for (size_t i{1}; i < curr_robots.size(); ++i) {
                if (curr_robots[i].moving_left &&
                    !curr_robots[i - 1].moving_left) {
                    next_collision_in = std::min(next_collision_in,
                        (curr_robots[i].position - curr_robots[i - 1].position +
                            1) /
                            2);
                }
            }

            if (next_collision_in == INT_MAX) {
                break;
            }

            for (size_t i{0}; i < curr_robots.size(); ++i) {
                auto &curr_robot = curr_robots[i];

                const int new_position =
                    curr_robot.position + (curr_robot.moving_left
                                                  ? -next_collision_in
                                                  : next_collision_in);

                if (!next_robots.empty() &&
                    next_robots.back().position >= new_position) {
                    if (next_robots.back().health == curr_robot.health) {

                        next_robots.pop_back();
                    } else if (next_robots.back().health > curr_robot.health) {
                        --next_robots.back().health;
                    } else {
                        --curr_robot.health;
                        curr_robot.position = new_position;
                        next_robots.back() = curr_robot;
                    }
                    continue;
                }
                curr_robot.position = new_position;
                next_robots.emplace_back(curr_robot);
            }

            curr_robots.clear();
        }

        std::sort(robots[r].begin(), robots[r].end(), [](const Robot &v1, const Robot &v2) {
            return v1.id < v2.id;
        });

        std::vector<int> result(robots[r].size());
        for (size_t i{0}; i < robots[r].size(); ++i) {
            result[i] = robots[r][i].health;
        }

        return result;
    }

  private:
    struct Robot {
        Robot(int position, int health, bool moving_left, uint id)
            : position(position), health(health), moving_left(moving_left),
              id(id) {}

        int position;
        int health;
        bool moving_left;
        uint id;
    };
};
