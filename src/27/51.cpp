#include <string>
#include <vector>

#include <algorithm>
#include <stack>

class Solution {
  public:
    std::vector<int> survivedRobotsHealths(std::vector<int> &positions,
        std::vector<int> &healths, std::string directions) {

        std::vector<Robot> robots;
        robots.reserve(positions.size());

        for (size_t i{0}; i < positions.size(); ++i) {
            robots.emplace_back(
                positions[i], healths[i], directions[i] == 'L', i);
        }

        std::ranges::sort(robots, [](const Robot &v1, const Robot &v2) {
                return v1.position < v2.position;
            });

        std::stack<Robot *> right_moving_robots;

        for (size_t i{0}; i < robots.size(); ++i) {
            auto &robot = robots[i];

            if (!robots[i].moving_left) {
                right_moving_robots.emplace(&robot);
                continue;
            }

            while (!right_moving_robots.empty() && robot.health > 0) {
                auto &right_robot = right_moving_robots.top();

                if (right_robot->health == robot.health) {
                    right_robot->health = 0;
                    robot.health = 0;
                    right_moving_robots.pop();
                } else if (right_robot->health < robot.health) {
                    right_robot->health = 0;
                    --robot.health;
                    right_moving_robots.pop();
                } else {
                    --right_robot->health;
                    robot.health = 0;
                }
            }
        }

        std::erase_if(
            robots, [](const Robot &robot) { return robot.health == 0; });

        std::ranges::sort(robots,
            [](const Robot &v1, const Robot &v2) { return v1.id < v2.id; });

        std::vector<int> result(robots.size());
        for (size_t i{0}; i < robots.size(); ++i) {
            result[i] = robots[i].health;
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
