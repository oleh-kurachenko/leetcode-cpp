#include <iostream>
#include <string>

#include <list>
#include <algorithm>

/**
 * it would be simpler just to simulate it directly, yet this variant is more
 * fun
 */
class Solution {
public:
    std::string processStr(std::string s) {
        std::list<char> result_list;
        bool swapped{false};

        for (const char c: s) {
            if (c == '*') {
                if (!result_list.empty()) {
                    if (!swapped)
                        result_list.pop_back();
                    else
                        result_list.pop_front();
                }
            } else if (c == '#') {
                if (!swapped) {
                    std::copy_n(result_list.begin(), result_list.size(),
                                std::back_inserter(result_list));
                } else {
                    std::copy_n(result_list.rbegin(), result_list.size(),
                                std::front_inserter(result_list));
                }
            } else if (c == '%') {
                swapped = !swapped;
            } else {
                if (swapped) {
                    result_list.push_front(c);
                } else {
                    result_list.push_back(c);
                }
            }
        }

        if (swapped) {
            return {result_list.rbegin(), result_list.rend()};
        }
        return {result_list.begin(), result_list.end()};
    }
};

int main() {
    std::cout << Solution().processStr("ab##################") << std::endl;
}
