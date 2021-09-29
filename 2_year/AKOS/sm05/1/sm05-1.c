#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef struct List_linked {
    int num;
    struct List_linked *prev;
} List_linked;

List_linked *Push_element(List_linked *head, int buf) {
    struct List_linked *element = calloc(1, sizeof(*element));
    element->prev = head;
    element->num = buf;
    return element;
}

int main(void) {
    int buf;
    struct List_linked *head = NULL;
    struct List_linked *tail = head;

    while (scanf("%d", &buf) != EOF) {
        head = Push_element(head, buf);
    }
    struct List_linked *tmp = head;   
    while (tmp) {
        printf("%d\n", tmp->num);
        // передвинули указатель
        tail = tmp -> prev;
        // очистили
        free(tmp);
        tmp = tail;
    }
    return 0;
}