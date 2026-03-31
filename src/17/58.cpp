#include <string>

class Solution {
  public:
    int minOperations(std::string s) {
        size_t even_varian_count{0};
        size_t odd_varian_count{0};

        for (size_t i{0}; i < s.size(); ++i) {
            if (s[i] - '0' == i % 2) {
                ++even_varian_count;
            }
            if (s[i] - '0' != i % 2) {
                ++odd_varian_count;
            }
        }

        return std::min(even_varian_count, odd_varian_count);
    }
};
