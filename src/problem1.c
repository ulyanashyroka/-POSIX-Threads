#include <stdio.h>
#include <pthread.h>

void *worker(void *arg) {
    (void)arg;
    printf("Hello from the worker thread!\n");
    return NULL;
}

int main(void) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, worker, NULL) != 0) {
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }
    if (pthread_join(thread, NULL) != 0) return 1;
    printf("Worker finished; main is exiting.\n");
    return 0;
}
