#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef double (*funcptr_t)(double a);

typedef struct FunctionTable {
    char *f_name;
    funcptr_t function;
} FuncTable;

static const FuncTable func_table[] = {
        {"sin",  &sin},
        {"cos",  &cos},
        {"exp",  &exp},
        {"log",  &log},
        {"tan",  &tan},
        {"sqrt", &sqrt}
};

int main() {
    double num;
    char f_name[100001];
    // Элементы ввода разделяются произвольным количеством пробельных символов.
    while (scanf("%s %lg", f_name, &num) == 2) {
        int flag_fname = 0;
        for (size_t i = 0; i != 6; ++i) {
            if (strcmp(func_table[i].f_name, f_name) != 0) continue;
            flag_fname = 1;
            printf("%a\n", func_table[i].function(num));
            break;
        }
        if (flag_fname == 0) {
            printf("%a\n", NAN);
        }
    }
    return 0;
}