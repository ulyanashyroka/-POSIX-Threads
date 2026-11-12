#include <stdio.h>
#include <pthread.h>

#define THREADS 5
#define INCREMENTS 1000

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
    (void)arg;
    for (int i = 0; i < INCREMENTS; ++i) {
        pthread_mutex_lock(&lock);
        ++counter;
        pthread_mutex_unlock(&lock);
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
    printf("Final counter: %d\n", counter);
    pthread_mutex_destroy(&lock);
    return 0;
}
