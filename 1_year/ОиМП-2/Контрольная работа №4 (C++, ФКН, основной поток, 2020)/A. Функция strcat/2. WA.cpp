namespace my_cstring {
    char *strcat(char *destination, const char *source) {
        // Находим 0, то есть конец по указателю
        while (*destination != '\0') {
            destination++;
        }
        *destination = *source;
        while (*destination != '\0') {
            source++;
            destination++;
            *destination = *source;
        }
    }
}