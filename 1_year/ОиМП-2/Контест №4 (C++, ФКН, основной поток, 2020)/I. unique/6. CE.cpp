template <typename Iter>
Iter unique(Iter first, Iter last) {
    if (first == last)
        return last;
    Iter result = first;
    while (++first != last) {
        if (!(*result == *first) && ++result != first) {
            *result = move(*first);
        }
    }
    return ++result;
}