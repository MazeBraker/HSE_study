template <typename Iter>
Iter unique(Iter first, Iter last) {
    if (first == last) {
        return last;
    }
    auto it = next(first);
    while (first != last) {
        if (*it == *first) {
            ++first;
        } else {
            ++first;
            *it = *first;
        }
    }
    return it;
}