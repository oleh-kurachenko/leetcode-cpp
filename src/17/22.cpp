#include <cstdint>

#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @note better solution using UnionFind exists
 */
class Solution {
  public:
    int minimumHammingDistance(std::vector<int> &source,
        std::vector<int> &target, std::vector<std::vector<int>> &allowedSwaps) {

        int result{0};

        build_swaps_graph(allowedSwaps);
        _visited.assign(source.size(), false);

        for (size_t i{0}; i < source.size(); ++i) {
            if (!_visited[i]) {
                _component.clear();
                _component_sources.clear();

                dfs(i, source);

                for (const auto idx : _component) {
                    if (const auto itr = _component_sources.find(target[idx]);
                        itr != _component_sources.end()) {
                        _component_sources.erase(itr);
                    } else {
                        ++result;
                    }
                }
            }
        }

        return result;
    }

  private:
    std::unordered_map<int, std::vector<int>> _swaps_graph{};
    std::vector<bool> _visited{};

    std::vector<int> _component{};
    std::unordered_multiset<int> _component_sources{};

    void build_swaps_graph(const std::vector<std::vector<int>> &allowedSwaps) {
        for (size_t i{0}; i < allowedSwaps.size(); ++i) {
            _swaps_graph[allowedSwaps[i][0]].push_back(allowedSwaps[i][1]);
            _swaps_graph[allowedSwaps[i][1]].push_back(allowedSwaps[i][0]);
        }
    }

    void dfs(const size_t idx, std::vector<int> &source) {
        _visited[idx] = true;
        _component.push_back(idx);
        _component_sources.insert(source[idx]);

        for (size_t i{0}; i < _swaps_graph[idx].size(); ++i) {
            const auto idx2 = _swaps_graph[idx][i];

            if (!_visited[idx2]) {
                dfs(idx2, source);
            }
        }
    }
};