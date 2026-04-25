#include <string>

class Solution {
  public:
    int furthestDistanceFromOrigin(const std::string moves) {
        int shift{0};
        int steps{0};

        for (const char c : moves) {
            switch (c) {
            case 'L':
                --shift;
                break;
            case 'R':
                ++shift;
                break;
            default:
                ++steps;
            }
        }

        return std::abs(shift) + steps;
    }
};