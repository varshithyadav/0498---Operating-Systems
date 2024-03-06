#include <stdio.h>
#include <pthread.h>
int counter = 0;
pthread_mutex_t mutex;
void *incrementCounter(void *arg);
int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("Final counter value: %d\n", counter);
    return 0;
}
void *incrementCounter(void *arg) {
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}
