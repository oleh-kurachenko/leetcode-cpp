#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstring>

#include <array>
#include <ranges>
#include <string>
#include <vector>

class Solution {
  public:
    using uint = uint16_t;

    int minimumDistance(std::string word) {
        std::vector<std::array<std::array<uint, NLETTERS>, NLETTERS>>
            steps_count(word.size());
        for (auto &steps_pos : steps_count) {
            std::memset(steps_pos.data(), UCHAR_MAX,
                NLETTERS * NLETTERS * sizeof(uint));
        }

        for (size_t l{0}; l < NLETTERS; ++l) {
            steps_count[0][l][word[0] - 'A'] = 0;
            steps_count[0][word[0] - 'A'][l] = 0;
        }

        for (size_t i{1}; i < word.size(); ++i) {
            const auto l{word[i] - 'A'};
            const auto prev_l{word[i - 1] - 'A'};

            const auto distance_prev = distance(l, prev_l);

            for (size_t l1{0}; l1 < NLETTERS; ++l1) {
                steps_count[i][l][l1] = std::min<uint>(steps_count[i][l][l1],
                    steps_count[i - 1][prev_l][l1] + distance_prev);
                steps_count[i][l1][l] = std::min<uint>(steps_count[i][l1][l],
                    steps_count[i - 1][l1][prev_l] + distance_prev);

                if (prev_l == l1) {
                    for (size_t l2{0}; l2 < NLETTERS; ++l2) {
                        const auto distance_l2 = distance(l, l2);

                        steps_count[i][l][l1] =
                            std::min<uint>(steps_count[i][l][l1],
                                steps_count[i - 1][l2][l1] + distance_l2);
                        steps_count[i][l1][l] =
                            std::min<uint>(steps_count[i][l1][l],
                                steps_count[i - 1][l1][l2] + distance_l2);
                    }
                }
            }
        }

        return std::ranges::min(
            steps_count.back() | std::views::transform([](auto steps_pos) {
                return std::ranges::min(steps_pos);
            }));
    }

  private:
    static constexpr size_t NLETTERS{'Z' - 'A' + 1};

    static uint distance(auto l1, auto l2) {
        const auto y1{l1 % 6};
        const auto y2{l2 % 6};

        return (l1 > l2 ? l1 / 6 - l2 / 6 : l2 / 6 - l1 / 6) +
               (y1 > y2 ? y1 - y2 : y2 - y1);
    }
};