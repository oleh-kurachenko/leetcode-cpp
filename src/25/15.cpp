#include <string>
#include <vector>

class Solution {
  public:
    int closestTarget(
        std::vector<std::string> &words, std::string target, int startIndex) {

        for (size_t i{0}; i < words.size() / 2 + 1; ++i) {
            if (target == words[(i + startIndex) % words.size()]) {
                return i;
            }
            if (target ==
                words[(words.size() - i + startIndex) % words.size()]) {
                return i;
            }
        }

        return -1;
    }
};