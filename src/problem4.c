#include <stdio.h>
#include <pthread.h>

void *count(void *arg) {
    int number = *(int *)arg;
    for (int i = 1; i <= 10; ++i) {
        printf("Thread %d: %d\n", number, i);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[3];
    int numbers[3] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&threads[i], NULL, count, &numbers[i]) != 0) return 1;
    }
    for (int i = 0; i < 3; ++i) {
        if (pthread_join(threads[i], NULL) != 0) return 1;
    }
    return 0;
}
