#include <iostream>
#include <vector>

#include <set>
#include <unordered_map>

class Solution {
  public:
    int robotSim(
        std::vector<int> &commands, std::vector<std::vector<int>> &obstacles) {

        std::unordered_map<int, std::set<int>> x_obstacles;
        std::unordered_map<int, std::set<int>> y_obstacles;

        for (size_t i{0}; i < obstacles.size(); ++i) {
            const int x{obstacles[i][0]};
            const int y{obstacles[i][1]};

            x_obstacles[x].insert(y);
            y_obstacles[y].insert(x);
        }

        int x{0};
        int y{0};

        int x_d{0};
        int y_d{1};

        int d_max{0};

        for (size_t i{0}; i < commands.size(); ++i) {
            if (commands[i] == -2) {
                if (y_d) {
                    x_d = -y_d;
                    y_d = 0;
                } else {
                    y_d = x_d;
                    x_d = 0;
                }
            } else if (commands[i] == -1) {
                if (y_d) {
                    x_d = y_d;
                    y_d = 0;
                } else {
                    y_d = -x_d;
                    x_d = 0;
                }
            } else {
                if (y_d) {
                    int y_upd{y + y_d * commands[i]};
                    auto &obst = x_obstacles[x];
                    if (y_d > 0) {
                        if (const auto next_obstacle = obst.upper_bound(y);
                            next_obstacle != obst.end()) {
                            y_upd = std::min(y_upd, *next_obstacle - 1);
                        }
                    } else {
                        if (auto next_obstacle = obst.lower_bound(y);
                            next_obstacle != obst.begin()) {
                            --next_obstacle;
                            y_upd = std::max(y_upd, *next_obstacle + 1);
                        }
                    }
                    y = y_upd;
                } else {
                    int x_upd{x + x_d * commands[i]};
                    auto &obst = y_obstacles[y];
                    if (x_d > 0) {
                        if (const auto next_obstacle = obst.upper_bound(x);
                            next_obstacle != obst.end()) {
                            x_upd = std::min(x_upd, *next_obstacle - 1);
                        }
                    } else {
                        if (auto next_obstacle = obst.lower_bound(x);
                            next_obstacle != obst.begin()) {
                            --next_obstacle;
                            x_upd = std::max(x_upd, *next_obstacle + 1);
                        }
                    }
                    x = x_upd;
                }
                d_max = std::max(d_max, x * x + y * y);
            }
        }

        return d_max;
    }
};
