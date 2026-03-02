#include <iostream>
#include <vector>

#include <array>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
        right(right) {
    }
};

class Solution {
private:
    static constexpr size_t NUMERIC_LIMIT{3000};

    TreeNode *build_tree(std::vector<int>::const_iterator preorder_begin,
                         std::vector<int>::const_iterator preorder_end,
                         std::vector<int>::const_iterator inorder_begin,
                         std::vector<int>::const_iterator inorder_end,
                         const std::array<std::vector<int>::const_iterator,
                             NUMERIC_LIMIT * 2 + 1> &inorder_map) {
        if (preorder_begin == preorder_end) {
            return nullptr;
        }

        const auto inorder_root_position = inorder_map[
            *preorder_begin + NUMERIC_LIMIT + 1];
        const size_t left_size = inorder_root_position - inorder_begin;

        return new TreeNode(*preorder_begin,
                            build_tree(preorder_begin + 1,
                                       preorder_begin + (left_size + 1),
                                       inorder_begin,
                                       inorder_root_position, inorder_map),
                            build_tree(preorder_begin + (left_size + 1),
                                       preorder_end, inorder_root_position + 1,
                                       inorder_end, inorder_map));
    }

public:
    TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
        std::array<std::vector<int>::const_iterator, NUMERIC_LIMIT * 2 + 1>
                inorder_map;
        for (auto itr = inorder.cbegin(); itr != inorder.cend(); ++itr) {
            inorder_map[*itr + NUMERIC_LIMIT + 1] = itr;
        }

        return build_tree(preorder.begin(), preorder.end(), inorder.begin(),
                          inorder.end(), inorder_map);
    }
};

int main() {
    std::vector preorder{3, 9, 20, 15, 7};
    std::vector inorder{9, 3, 15, 20, 7};

    auto node = Solution().buildTree(preorder, inorder);

    return 0;
}
