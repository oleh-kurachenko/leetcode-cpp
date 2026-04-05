#include <string>

class Solution {
  public:
    bool judgeCircle(std::string moves) {
        int x{0};
        int y{0};

        for (const char c : moves) {
            switch (c) {
            case 'R':
                ++y;
                break;
            case 'L':
                --y;
                break;
            case 'U':
                ++x;
                break;
            case 'D':
                --x;
                break;
            default:
                break;
            }
        }

        return !x && !y;
    }
};