#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/eventfd.h>
// сделано на семинаре 1911
enum {
    STATUS_ACTIVATE = 1,
    STATUS_EXIT = 2,
};

typedef struct thread_context {
    int thread_id;
    pthread_t thread;
    int event_fd;
    struct thread_context* begin;
    size_t threads_count;
} thread_context_t;

void* thread_func(void* ctx_void) {
    thread_context_t* ctx = (thread_context_t*)ctx_void;
    while (1) {
        eventfd_t value;
        eventfd_read(ctx->event_fd, &value);
        if (value == STATUS_EXIT) {
            break;
        }

        int32_t input_value;
        if (scanf("%"SCNd32, &input_value) != 1) {
            for (size_t i = 0; i < ctx->threads_count; i++) {
                eventfd_write(ctx->begin[i].event_fd, STATUS_EXIT);
            }
            continue;
        }
        printf("%d %"PRId32"\n", ctx->thread_id, input_value);

        int64_t x = input_value % ((int64_t)ctx->threads_count);
        if (x < 0) {
            x += ((int64_t)ctx->threads_count);
        }
        size_t next = (size_t)x;
        eventfd_write(ctx->begin[next].event_fd, STATUS_ACTIVATE);
        if (next != (size_t)ctx->thread_id) {
            sched_yield();
        }
    }
    return NULL;
}

int main(int argc, char** argv) {
    int thread_count = atoi(argv[1]);
    thread_context_t* contexts = (thread_context_t*)calloc(
        thread_count,
        sizeof(*contexts)
    );

    for (int i = 0; i < thread_count; i++) {
        contexts[i].begin = contexts;
        contexts[i].event_fd = eventfd(0, 0);
        contexts[i].thread_id = i;
        contexts[i].threads_count = (size_t)thread_count;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, 16384);
        pthread_create(&contexts[i].thread, &attr, &thread_func, &contexts[i]);
    }

    eventfd_write(contexts[0].event_fd, STATUS_ACTIVATE);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(contexts[i].thread, NULL);
        close(contexts[i].event_fd);
    }

    return 0;
}