#include <vector>
#include <iostream>

#include <cstdint>
#include <algorithm>
#include <array>

class Solution {
private:
    static const std::array<std::array<char, 2>, 3> LEX;

public:
    std::string getHappyString(int n, int k) {
        --k;

        std::vector<uint8_t> option(n - 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            option[i] = k % 2;
            k /= 2;
        }

        if (k > 2) {
            return "";
        }

        std::string result(n, ' ');
        result[0] = k % 3 + 'a';

        std::ranges::reverse(option);
        for (int i = 0; i < n - 1; ++i) {
            result[i + 1] = LEX[result[i] - 'a'][option[i]];
        }

        return result;
    }
};

const std::array<std::array<char, 2>, 3> Solution::LEX{
    std::array{'b', 'c'}, {'a', 'c'}, {'a', 'b'}
};

int main() {
    std::cout << Solution().getHappyString(3, 9) << std::endl;
}
