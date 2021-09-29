#include <stdio.h>
#include <stdlib.h>

struct List_linked {
    int num;
    int count;
    struct List_linked *next;
    struct List_linked *prev;
};

int
main() {
    int new_buf;
    struct List_linked *new_num;
    struct List_linked *head;

    if (scanf("%d", &new_buf) != EOF) {
            head = calloc(1, sizeof(*new_num));
            head->num = new_buf;
            head->count = 1;
            head->next = head;
            head->prev = head;
        while (scanf("%d", &new_buf) != EOF) {
            if (head->num == new_buf) {
                ++(head->count);
            } else {
                new_num = head->next;
                while (new_num->next != head && new_num->num != new_buf) {
                    new_num = new_num->next;
                }

                if (new_num->num == new_buf) {
                    new_num->count += 1;
                    new_num->next->prev = new_num->prev;
                    new_num->prev->next = new_num->next;
                } else {
                    new_num = calloc(1, sizeof(*new_num));
                    new_num->num = new_buf;
                    new_num->count = 1;
                }

                new_num->next = head;
                head->prev->next = new_num;
                new_num->prev = head->prev;
                head->prev = new_num;
                head = new_num;
            }
        }

        new_num = head->prev;
        while (new_num != head) {
            printf("%d %d\n", new_num->num, new_num->count);
            new_num = new_num->prev;
            free(new_num->next);
        }
        printf("%d %d\n", new_num->num, new_num->count);
        free(new_num);
    }

    return 0;
}