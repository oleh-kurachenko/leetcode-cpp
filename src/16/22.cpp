#include <iostream>

#include <cstdint>
#include <vector>

#include "../algorithms/inverse_multiplier_modulo.cpp"

class Fancy {
  public:
    void append(int val) {
        entries.push_back(Entry{static_cast<uint16_t>(val),
            entries.back().multiplier, entries.back().addend});
    }

    void addAll(int inc) {
        entries.back().addend += inc;
        entries.back().addend %= MODULO;
    }

    void multAll(int m) {
        entries.back().multiplier *= m;
        entries.back().multiplier %= MODULO;
        entries.back().addend *= m;
        entries.back().addend %= MODULO;
    }

    int getIndex(int idx) {
        if (idx >= entries.size() - 1) {
            return -1;
        }

        uint64_t effective_multiplier{
            entries.back().multiplier *
            inverse_multiplier_modulo<uint64_t, MODULO>(
                entries[idx].multiplier) %
            MODULO};

        uint64_t effective_addend{
            (entries.back().addend + MODULO -
                entries[idx].addend * effective_multiplier % MODULO) %
            MODULO};

        return static_cast<int>(
            (entries[idx + 1].initial_value * effective_multiplier +
                effective_addend) %
            MODULO);
    }

  private:
    static constexpr uint64_t MODULO{1'000'000'007};

    struct Entry {
        uint16_t initial_value;
        uint64_t multiplier{1};
        uint64_t addend{0};
    };

    std::vector<Entry> entries{{0, 1, 0}};
};

int main() {
    Fancy fancy;

    fancy.append(2);  // fancy sequence: [2]
    fancy.addAll(3);  // fancy sequence: [2+3] -> [5]
    fancy.append(7);  // fancy sequence: [5, 7]
    fancy.multAll(2); // fancy sequence: [5*2, 7*2] -> [10, 14]
    std::cout << fancy.getIndex(0) << std::endl; // return 10
    fancy.addAll(3);  // fancy sequence: [10+3, 14+3] -> [13, 17]
    fancy.append(10); // fancy sequence: [13, 17, 10]
    fancy.multAll(2); // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
    std::cout << fancy.getIndex(0) << std::endl; // return 26
    std::cout << fancy.getIndex(1) << std::endl; // return 34
    std::cout << fancy.getIndex(2) << std::endl; // return 20

    return 0;
}
