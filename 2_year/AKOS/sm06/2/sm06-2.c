#include<stdio.h>
#include<stdlib.h>
// вдохновлен семинаром 199 группы 
// enum { SIZE = 5 };

// void qsort_r(void *base, size_t nmemb, size_t size,
// int (*compar)(const void *, const void *, void *), void *arg);
// first, second - индексы
// везде используется линуксовый порядок аргументов
static int cmp(const void *first, const void *second, void *ptr) {
//int cmp(void *ptr, const void *f, const void *s) {
    int f = *(const int *) first;
    int s = *(const int *) second;
    const int *data = ptr;
    if (data[f] == data[s]) {
        // порядок сохрн
        return f - s;
    }
    // 0 нельзя возвращать из-за не стабильной сортировки qsort
    if (data[f] < data[s]) {
        return -1;
    } else {
        return 1;
    }
}


void process(size_t count, int *data, int *order) {
    for (int i = 0; i < count; i++) {
        order[i] = i;
    }
    qsort_r(order, count, sizeof(*order), cmp, (void *)data);
    //qsort_r(order, count, sizeof(*order), data, cmp);
}
/*
int main() {
    int* data = malloc(SIZE * sizeof(*data));
    if (data == NULL) {
        fprintf(stderr, "bad malloc");
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        data[i] = SIZE - i;
    }
    int* order = malloc(SIZE * sizeof(*order));
    if (order == NULL) {
        fprintf(stderr, "bad malloc");
        return 1;
    }
    process(SIZE, data, order);
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
    return 0;
}*/