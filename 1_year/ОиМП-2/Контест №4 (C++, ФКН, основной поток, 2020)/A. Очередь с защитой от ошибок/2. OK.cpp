template < class It, class T >
void fill_range(It first, It last, const T& value) {
    while (first != last) {
        *first = value;
        ++first;
    }
}