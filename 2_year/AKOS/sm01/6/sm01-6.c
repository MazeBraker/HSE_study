#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int is_garbage(int k) {
    return k != '.' && !isdigit(k);
}

int main() {
    int k;
    char *str = (char *) malloc(256 * sizeof(char));
    char *str1 = (char *) malloc(256 * sizeof(char));
    while ((k = getchar()) != EOF){
        if (is_garbage(k)) {
            continue;
        }
        // num - целая часть, num1 - число после точки
        int i = 0, j = 0, is_float = 0;
        double sum1 = 0;
        double w = 0;
        double sum = 0;
        memset(str, 0, 256 * sizeof(char));
        memset(str1, 0, 256 * sizeof(char));
        do {
            if (k == '\n') { break; }
            if (isdigit(k)) {
                str[i++] = (char) (k - '0');
            } else if (k == '.') {
                void *temp = str;
                str = str1;
                str1 = temp;
                memset(str, 0, 256 * sizeof(char));
                j = i;
                i = 0;
                is_float = 1;
            }
        } while (!is_garbage((k = getchar())));
        if (!is_float) {
            while (i > 0) {
                sum += str[i - 1] * (double) round(pow(7, w++));
                i--;
            }
        } else {
            while (j > 0) {
                sum += str1[j - 1] * (double) round(pow(7, w++));
                j--;
            }
            while (i > 0) {
                sum1 += str[i - 1] * pow(7, -i);
                i--;
            }
        }
        if (!is_float) {
            printf("%.10g\n", sum);
        } else {
            printf("%.10g\n", (double)sum + sum1);
        }
    }
    free(str);
    free(str1);
    return 0;
}