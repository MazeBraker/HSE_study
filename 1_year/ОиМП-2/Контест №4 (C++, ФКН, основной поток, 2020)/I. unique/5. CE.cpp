template <typename InIter, typename OutIter, typename Predicate>
OutIter remove_copy_if(InIter first, InIter last, OutIter out, Predicate f) {
    for (; first != last; ++first)
        if (!f(*first))
            *out++ = *first;
    return out;
}