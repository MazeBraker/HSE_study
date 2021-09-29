namespace my_cstring {
    char *strcat(char *destination, const char *source) {
        char *k = destination;
        const char *l = source;
        char *nachalo = destination;
        for (char *k = destination; *(k) != '\0'; k++) {}
        for (const char *l = source; *(l) != '\0'; l++) {}
        *k = '\0';
        return nachalo;
    }
}