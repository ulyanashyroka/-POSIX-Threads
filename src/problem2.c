#include <stdio.h>
#include <pthread.h>

void *worker(void *arg) {
    int number = *(int *)arg;
    printf("Thread %d: ID %lu\n", number, (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t threads[5];
    int numbers[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        if (pthread_create(&threads[i], NULL, worker, &numbers[i]) != 0) return 1;
    }
    for (int i = 0; i < 5; ++i) {
        if (pthread_join(threads[i], NULL) != 0) return 1;
    }
    return 0;
}
