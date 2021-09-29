namespace my_cstring {
    char * strcat(char * destination, const char * source) {
        char * i = destination;
        char * nachalo = destination;
        const char * j = source;
        while (*destination != '\0') {
            i++;
        }
        while (*source != '\0') {
            *i++ = *j++;
        }
        *i = '\0';
        return nachalo;
    }
}