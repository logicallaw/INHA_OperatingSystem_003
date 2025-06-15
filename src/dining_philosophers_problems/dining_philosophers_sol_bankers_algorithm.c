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

// Define safety status for Banker's algorithm
typedef enum { UNSAFE = 0, SAFE = 1 } safety_t;

// For mutual exclusion of Metrix
pthread_mutex_t bankers_mutex;
// For condition variable for Process Allocation Denial
pthread_cond_t bankers_cond;

sem_t forks[NUM];

// C means claim metrix
int C[NUM][NUM];
// A means allocation metrix
int A[NUM][NUM];
// V means available vector
int V[NUM];

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

void tables_init() {
  for (int j = 0; j < NUM; j++) {
    // Each resource has one and initializes to one.
    V[j] = 1;
    for (int i = 0; i < NUM; i++) {
      // Initially, there are no allocated resources, so they are all
      // initialized to zero.
      A[i][j] = 0;
      // Find and reset the left fork and the right fork.
      C[i][j] = (j == i || j == (i + 1) % NUM) ? 1 : 0;
    }
  }
}

void bankers_request(int philosopher_num) {
  // Request vector means the number of additional instances that Worst-case can
  // request.
  int request[NUM];
  safety_t is_safe;

  for (int j = 0; j < NUM; j++) {
    request[j] = C[philosopher_num][j] - A[philosopher_num][j];
  }

  pthread_mutex_lock(&bankers_mutex);
  do {
    is_safe = SAFE;
    for (int j = 0; j < NUM; j++) {
      if (request[j] > V[j]) {
        is_safe = UNSAFE;
        break;
      }
    }
    // If it's unsafe, go to sleep.
    if (is_safe == UNSAFE) {
      pthread_cond_wait(&bankers_cond, &bankers_mutex);
    }
  } while (is_safe == UNSAFE);

  // If it's safe, absolutely no deadlock.
  for (int j = 0; j < NUM; j++) {
    V[j] -= request[j];
    A[philosopher_num][j] += request[j];
  }
  pthread_mutex_unlock(&bankers_mutex);
}

void bankers_release(int philosopher_num) {
  pthread_mutex_lock(&bankers_mutex);
  for (int j = 0; j < NUM; j++) {
    V[j] += A[philosopher_num][j];
    A[philosopher_num][j] = 0;
  }
  // Waking up all the sleeping threads.
  pthread_cond_broadcast(&bankers_cond);
  pthread_mutex_unlock(&bankers_mutex);
}

void *philosopher(void *arg) {
  int philosopher_num;
  philosopher_num = (unsigned long int)arg;

  while (1) {
    bankers_request(philosopher_num);

    pickup(philosopher_num);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           philosopher_num);
    pickup(philosopher_num + 1);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);
    eating(philosopher_num);

    putdown(philosopher_num);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);
    putdown(philosopher_num + 1);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           philosopher_num);

    bankers_release(philosopher_num);

    thinking(philosopher_num);
  }
  return NULL;
}

int main() {
  pthread_t threads[NUM];

  for (int i = 0; i < NUM; i++) {
    sem_init(&forks[i], 0, 1);
  }

  pthread_mutex_init(&bankers_mutex, NULL);
  pthread_cond_init(&bankers_cond, NULL);

  tables_init();

  for (unsigned long int i = 0; i < NUM; i++) {
    pthread_create(&threads[i], NULL, philosopher, (void *)i);
  }

  for (int i = 0; i < NUM; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("NO DEADLOCK\n");
  return 0;
}