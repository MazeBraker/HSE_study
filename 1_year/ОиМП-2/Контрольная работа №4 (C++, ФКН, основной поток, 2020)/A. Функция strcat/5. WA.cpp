namespace my_cstring {
    char * strcat(char * destination, const char * source) {
        char * current = destination;
        while (*current) {
            ++current;
        }
        while (*current++ = *source++) {
        }
        return destination;
    }
}