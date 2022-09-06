#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>


#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];

typedef int semaphore;

semaphore mutex = 1;
semaphore philho[N];

void test(int i) {
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[i] = EATING;
    sem_post(&philho[i]);
  }
}

void take_forks(int i) {
  sem_wait(&mutex);
  state[i] = HUNGRY;
  test(i);
  sem_post(&mutex);
  sem_wait(&philho[i]);
}

void put_forks(int i) {
  sem_wait(&mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void *philosopher(void *arg) {
  int i = (int)arg;
  while (1) {
    printf("Philosopher %d is thinking\n", i);
    take_forks(i);
    printf("Philosopher %d is eating\n", i);
    put_forks(i);
    }
}

int main() {
  int i;
  pthread_t tid[N];
  for (i = 0; i < N; i++) {
    sem_init(&philho[i], 0, 0);
  }
  for (i = 0; i < N; i++) {
    pthread_create(&tid[i], NULL, philosopher, (void *)i);
  }
  for (i = 0; i < N; i++) {
    pthread_join(tid[i], NULL);
  }
  return 0;
}