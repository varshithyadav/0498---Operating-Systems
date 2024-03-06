#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
pthread_mutex_t forks[NUM_PHILOSOPHERS];
void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;
    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(rand() % 3);
        printf("Philosopher %d is hungry and trying to pick up forks.\n", philosopher_id);
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up the left fork (%d).\n", philosopher_id, left_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up the right fork (%d).\n", philosopher_id, right_fork);
        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(rand() % 3);
        printf("Philosopher %d finished eating and is putting down forks.\n", philosopher_id);
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
    }
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}
