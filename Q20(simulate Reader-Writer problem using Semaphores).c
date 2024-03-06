#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_READERS 3
#define NUM_WRITERS 2
int sharedCounter = 0;
sem_t mutex, wrt;
int readCount = 0;
void *reader(void *arg);
void *writer(void *arg);
int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)(intptr_t)i);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)(intptr_t)i);
    }
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
void *reader(void *arg) {
    int readerID = (intptr_t)arg;
    while (1) {
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Reader %d is reading. Shared Counter: %d\n", readerID, sharedCounter);
        sleep(1);
        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
        sleep(2);    }
    pthread_exit(NULL);
}
void *writer(void *arg) {
    int writerID = (intptr_t)arg;
    while (1) {
        sem_wait(&wrt);
        sharedCounter++;
        printf("Writer %d is writing. Shared Counter: %d\n", writerID, sharedCounter);
        sem_post(&wrt);
        sleep(2);
		    }
    pthread_exit(NULL);
}
