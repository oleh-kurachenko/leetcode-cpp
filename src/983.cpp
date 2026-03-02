#include <iostream>
#include <vector>

#include <cstdint>
#include <algorithm>

class Solution {
private:
    static constexpr uint16_t MAX_DAYS {365};
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
        std::vector<int> min_cost(MAX_DAYS + 1, 0);

        size_t i_day{1};
        auto day = days.begin();

        for (; i_day <= days[days.size() - 1]; ++i_day) {
            if (i_day == *day) {
                ++day;

                min_cost[i_day] = std::min({
                    min_cost[i_day - 1] + costs[0],
                    min_cost[i_day < 7 ? 0 : i_day - 7] + costs[1],
                    min_cost[i_day < 30 ? 0 : i_day - 30] + costs[2]
                });
            } else {
                min_cost[i_day] = min_cost[i_day - 1];
            }
        }

        return min_cost[i_day - 1];
    }
};

int main() {
    std::vector<int> days {1,2,3,4,5,6,7,8,9,10,30,31};
    std::vector<int> costs {2,7,15};

    std::cout << Solution().mincostTickets(days, costs) << std::endl;
}
