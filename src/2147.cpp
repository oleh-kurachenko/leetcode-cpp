#include <iostream>
#include <string>

#include <cstdint>
#include <optional>

class Solution {
private:
    static constexpr uint64_t MOD{1'000'000'007};
    static constexpr char SEAT{'S'};

public:
    std::optional<std::size_t> next_seat_position(
        const std::string &corridor, size_t search_start_position) {
        for (size_t i{search_start_position}; i < corridor.length(); ++i) {
            if (corridor[i] == SEAT) {
                return {i};
            }
        }
        return std::nullopt;
    }

    int numberOfWays(std::string corridor) {
        size_t variants{1};

        auto last_seat = next_seat_position(corridor, 0);
        if (!last_seat) {
            return 0;
        }
        last_seat = next_seat_position(corridor, last_seat.value() + 1);
        if (!last_seat) {
            return 0;
        }

        for (;;) {
            auto next_seat =
                    next_seat_position(corridor, last_seat.value() + 1);
            if (!next_seat) {
                return variants;
            }
            variants = variants * (next_seat.value() - last_seat.value()) % MOD;
            last_seat = next_seat_position(corridor, next_seat.value() + 1);
            if (!last_seat) {
                return 0;
            }
        }
    }
};

int main() {
    std::cout << Solution().numberOfWays("PPSSPPPSSPPSSPPPPPPPPPPPPPP") <<
            std::endl;
}
