#include <iostream>
#include <vector>

#include <cstdint>
#include <sstream>
#include <functional>

class Solution {
private:
    std::ostringstream solution;

    void find_and_append_solutions(
        std::vector<std::string> &result,
        std::vector<int64_t> &digits,
        std::vector<char> &operations,
        size_t current_digit,
        std::function<int64_t(int64_t)> make_addition_group,
        std::function<int64_t(int64_t)> make_multiplication_group,
        int64_t target) {
        int64_t current_number{0};
        for (size_t i{current_digit}; i < digits.size(); ++i) {
            current_number = current_number * 10 + digits[i];

            find_and_append_solutions(result, digits, operations, i + 1,
                                          make_addition_group(current_number),
                                          make_multiplication_group(
                                              current_number), target);
            if (digits[current_digit] == 0) {
                return;
            }
        }
    }

    void find_and_append_solutions(std::vector<std::string> &result, std::vector<int64_t> &digits,
                                          std::vector<char> &operations,
                                          size_t current_digit,
                                          int64_t current_addition_group,
                                          int64_t
                                          currenct_multiplication_group,
                                          int64_t target) {
        if (current_digit == digits.size()) {
            if (current_addition_group + currenct_multiplication_group ==
                target) {
                solution.str("");

                solution << digits[0];
                for (size_t i{1}; i < digits.size(); ++i) {
                    if (operations[i] != ' ') {
                        solution << operations[i];
                    }
                    solution << digits[i];
                }

                result.push_back(solution.str());
            }
            return;
        }

        operations[current_digit] = '+';
        find_and_append_solutions(result, digits, operations, current_digit,
                                  [=](int64_t) {
                                      return current_addition_group +
                                             currenct_multiplication_group;
                                  }, [](int64_t current_number) {
                                      return current_number;
                                  }, target);

        if (current_digit == 0) {
            return;
        }

        operations[current_digit] = '-';
        find_and_append_solutions(result, digits, operations, current_digit,
                                  [=](int64_t) {
                                      return current_addition_group +
                                             currenct_multiplication_group;
                                  }, [](int64_t current_number) {
                                      return -current_number;
                                  }, target);

        operations[current_digit] = '*';
        find_and_append_solutions(result, digits, operations, current_digit,
                                  [=](int64_t) {
                                      return current_addition_group;
                                  }, [=](int64_t current_number) {
                                      return currenct_multiplication_group *
                                             current_number;
                                  }, target);

        operations[current_digit] = ' ';
    }

public:
    std::vector<std::string> addOperators(std::string num, int target) {
        std::vector<int64_t> digits{};
        digits.reserve(num.size());
        for (char c: num) {
            digits.push_back(c - '0');
        }

        std::vector operations(num.size(), ' ');

        std::vector<std::string> solutions{};
        find_and_append_solutions(solutions, digits, operations, 0, 0, 0, target);
        return solutions;
    }
};

int main() {
    const auto result = Solution().addOperators("010100", -100);

    for (const auto &s: result) {
        std::cout << "> " << s << std::endl;
    }
}
