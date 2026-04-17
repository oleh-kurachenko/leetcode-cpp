template<typename UIntT>
UIntT abs_diff(UIntT v1, UIntT v2) {
    return v1 > v2 ? v1 - v2 : v2 - v1;
}
