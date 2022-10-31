#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
    int a;
    int b;
};

void *sum (void *arg) {
    struct arguments *args = (struct arguments *) arg;
    float* result = malloc(sizeof(float));
    *result = args->a + args->b;
    return (void *) result;
}

int main() {
    pthread_t thread;
    struct arguments args;
    args.a = 10;
    args.b = 60;
    pthread_create(&thread, NULL, sum, (void *) &args);
    float* result;
    pthread_join(thread, (void **) &result);
    printf("Result: %.2f\n", *result);
    free(result);
    return 0;
}