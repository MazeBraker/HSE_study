// разобрали на семе
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <math.h>
#include <dirent.h>


int main(int argc, char** argv) {
    void* lib = dlopen("/lib/aarch64-linux-gnu/libm.so.6", RTLD_LAZY);
    double(*call)(double f) = (double (*)(double f))dlsym(lib, argv[1]);
    if (call == NULL) {
        perror("not found");
        return -1;
    }
    double x;
    while (scanf("%lf", &x) == 1) {
        printf("%.10g\n", call(x));
    }
    return 0;
}