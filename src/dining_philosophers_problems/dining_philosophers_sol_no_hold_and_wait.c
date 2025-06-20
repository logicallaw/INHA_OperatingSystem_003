/*
 * This is file of the project INHA_OperatingSystem_003
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-06-15
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define NUM 5

sem_t forks[NUM];
sem_t once;

void pickup(int philosopher_num) { sem_wait(&forks[philosopher_num % NUM]); }

void putdown(int philosopher_num) { sem_post(&forks[philosopher_num % NUM]); }

void thinking(int philosopher_num) {
  printf("philosopher %d is thinking\n", philosopher_num);
  return;
}

void eating(int philosopher_num) {
  printf("philosopher %d is eating\n", philosopher_num);
  return;
}

void *philosopher(void *arg) {
  int philosopher_num;
  philosopher_num = (unsigned long int)arg;

  while (1) {
    sem_wait(&once);
    pickup(philosopher_num);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           philosopher_num);
    pickup(philosopher_num + 1);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);
    sem_post(&once);

    eating(philosopher_num);

    putdown(philosopher_num);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);
    putdown(philosopher_num + 1);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           philosopher_num);

    thinking(philosopher_num);
  }
  return NULL;
}

int main() {
  pthread_t threads[NUM];

  for (int i = 0; i < NUM; i++) {
    sem_init(&forks[i], 0, 1);
  }

  sem_init(&once, 0, 1);

  for (unsigned long int i = 0; i < NUM; i++) {
    pthread_create(&threads[i], NULL, philosopher, (void *)i);
  }

  for (int i = 0; i < NUM; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("NO DEADLOCK\n");
  return 0;
}