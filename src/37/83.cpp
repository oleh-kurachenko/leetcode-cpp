#include <cstdint>

#include "../algorithms/abs_diff.cpp"

class Solution {
  public:
    int mirrorDistance(int n) { return abs_diff<uint>(n, get_reversed(n)); }

  private:
    using uint = uint64_t;

    uint get_reversed(const uint n) {

        uint reversed_n{0};
        uint copy_n{n};

        while (copy_n != 0) {
            reversed_n = reversed_n * 10 + copy_n % 10;
            copy_n = copy_n / 10;
        }

        return reversed_n;
    }
};