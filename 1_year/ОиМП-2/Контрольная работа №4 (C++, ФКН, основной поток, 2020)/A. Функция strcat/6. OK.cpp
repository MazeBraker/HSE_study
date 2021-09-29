namespace my_cstring {
    char * strcat(char * destination, const char * source) {
        char * nachalo = destination;
        while (*destination != '\0') {
            destination++;
        }
        while (*destination != '\0') {
            *destination++ = *source++;
        }
        *destination = '\0';
        return nachalo;
    }
}