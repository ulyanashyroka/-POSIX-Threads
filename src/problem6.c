#include <stdio.h>
#include <pthread.h>

#define THREADS 5
#define INCREMENTS 1000

int counter = 0;

void *increment(void *arg) {
    (void)arg;
    for (int i = 0; i < INCREMENTS; ++i) {
        ++counter; /* Intentional data race for the assignment. */
    }
    return NULL;
}

int main(void) {
    pthread_t threads[THREADS];
    for (int i = 0; i < THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) return 1;
    }
    for (int i = 0; i < THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) return 1;
    }
    printf("Expected counter: %d\n", THREADS * INCREMENTS);
    printf("Actual counter: %d\n", counter);
    return 0;
}
