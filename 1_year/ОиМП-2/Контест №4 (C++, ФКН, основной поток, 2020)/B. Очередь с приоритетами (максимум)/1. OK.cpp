template <typename Iter>
Iter unique(Iter first, Iter last) {
    if (first == last) return last;
    Iter res = first;
    while (first != last)
        if (*res != *first)
            *(++res) = first;
    first++;
    return res;
}