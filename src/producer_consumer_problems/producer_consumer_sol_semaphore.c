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
#define ITER 1000
#define MAX 30

void *producer(void *arg);
void *consumer(void *arg);

sem_t mutex, empty, fill;

int x;

int main() {
  pthread_t tid1, tid2;

  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, MAX);
  sem_init(&fill, 0, 0);

  pthread_create(&tid1, NULL, producer, NULL);
  pthread_create(&tid2, NULL, consumer, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  sem_destroy(&fill);
  sem_destroy(&empty);
  sem_destroy(&mutex);

  if (x != 0) {
    printf("BOOM! counter=%d\n", x);
  } else {
    printf("OK counter=%d\n", x);
  }
}

void *producer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&empty);
    sem_wait(&mutex);
    x++;
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    sem_post(&mutex);
    sem_post(&fill);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&fill);
    sem_wait(&mutex);
    x--;
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    sem_post(&mutex);
    sem_post(&empty);
  }
  return NULL;
}