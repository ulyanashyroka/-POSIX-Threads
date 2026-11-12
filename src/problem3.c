#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *calculate_sum(void *arg) {
    (void)arg;
    int *result = malloc(sizeof *result);
    if (result == NULL) return NULL;
    *result = 0;
    for (int i = 1; i <= 100; ++i) *result += i;
    return result;
}

int main(void) {
    pthread_t thread;
    void *returned = NULL;
    if (pthread_create(&thread, NULL, calculate_sum, NULL) != 0) return 1;
    if (pthread_join(thread, &returned) != 0) return 1;
    if (returned == NULL) return 1;
    int *sum = returned;
    printf("Sum from 1 to 100 = %d\n", *sum);
    free(sum);
    return 0;
}
