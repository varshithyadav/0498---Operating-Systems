#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *threadFunction1(void *arg) {
    printf("Thread 1 is running.\n");
    printf("Thread 1 is done.\n");
    pthread_exit(NULL);
}
void *threadFunction2(void *arg) {
    printf("Thread 2 is running.\n");
    printf("Thread 2 is done.\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t thread1, thread2;
	if (pthread_create(&thread1, NULL, threadFunction1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1.\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread2, NULL, threadFunction2, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2.\n");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread is done.\n");

    return 0;
}
