#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::string> twoEditWords(
        const std::vector<std::string> &queries,
        const std::vector<std::string> &dictionary) {

        std::vector<std::string> result;
        for (const auto &query : queries) {
            for (const auto &word : dictionary) {
                size_t diff_count{0};

                for (size_t i{0}; i < word.length(); ++i) {
                    if (query[i] != word[i]) {
                        if (++diff_count > 2) {
                            break;
                        }
                    }
                }

                if (diff_count <= 2) {
                    result.push_back(query);
                    break;
                }
            }
        }

        return result;
    }
};