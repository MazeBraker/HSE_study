#include<stdio.h>
#include<stdlib.h>
// вдохновлено семинаром 199
enum {
    multip = 1103515245,
    add = 12345,
    mod = 1 << 31
};

typedef struct RandomOperations {
    int (*next)(void *rg);

    void (*destroy)(void *rg);
} RandomOperations;

typedef struct RandomGenerator {
    long long x;
    struct RandomOperations *ops;
} RandomGenerator;

int next(void *rg1) {
    RandomGenerator *rg = rg1;
    rg->x = (rg->x * multip + add) % mod;
    return rg->x;
}

void destroy(void *rg1) {
    RandomGenerator *rg = rg1;
    free(rg->ops);
    free(rg);
}

RandomGenerator *random_create(int seed) {
    RandomGenerator *rg = malloc(sizeof(RandomGenerator));
    if (!rg) {
        fprintf(stderr, "bad malloc");
        exit(1);
    }
    rg->x = seed;
    rg->ops = malloc(sizeof(RandomOperations));
    if (rg->ops == NULL) {
        fprintf(stderr, "bad malloc");
        exit(1);
    }
    rg->ops->next = &next;
    rg->ops->destroy = &destroy;
    return rg;
}
/*
int main() {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
}*/