#include <string>

#include <unordered_set>
#include <vector>

/**
 * @note plain-old count-sort seems to be way faster
 * @note it's a pretty fun thing that leetcode "AI" as of 2026-03-30 evaluates
 *       this solution as "Perfect efficiency achieved; your solution is
 *       optimally fast and space-conscious."
 */
class Solution {
public:
    bool checkStrings(std::string s1, std::string s2) {
        constexpr std::size_t n_slices{2};
        constexpr std::size_t reserve{('z' - 'a') * 2};

        const size_t n{s1.length()};

        std::vector<std::unordered_multiset<char>> registry1(n_slices);
        std::vector<std::unordered_multiset<char>> registry2(n_slices);

        for (size_t i{0}; i < n_slices; ++i) {
            registry1[i].reserve(reserve);
            registry2[i].reserve(reserve);
        }

        for (size_t i{0}; i < n; ++i) {
            registry1[i % 2].emplace(s1[i]);
            registry2[i % 2].emplace(s2[i]);
        }

        return registry1[0] == registry2[0] && registry1[1] == registry2[1];
    }
};
