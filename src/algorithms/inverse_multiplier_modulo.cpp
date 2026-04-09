template<typename UIntT, UIntT MODULO>
UIntT inverse_multiplier_modulo(const UIntT value) {
    UIntT result{1};
    UIntT multiplier{value};
    UIntT remaining_power{MODULO - 2};

    while (remaining_power) {
        if (remaining_power % 2) {
            result *= multiplier;
            result %= MODULO;
        }

        multiplier *= multiplier;
        multiplier %= MODULO;
        remaining_power /= 2;
    }

    return result;
}
