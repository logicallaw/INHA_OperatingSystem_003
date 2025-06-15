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
#include <stdio.h>
#define ITER 1000
#define MAX 30

void *producer(void *arg);
void *consumer(void *arg);

pthread_mutex_t mutex;
pthread_cond_t empty, fill;
int x;

int main() {
  pthread_t tid1, tid2;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&empty, NULL);
  pthread_cond_init(&fill, NULL);

  pthread_create(&tid1, NULL, producer, NULL);
  pthread_create(&tid2, NULL, consumer, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  pthread_cond_destroy(&fill);
  pthread_cond_destroy(&empty);
  pthread_mutex_destroy(&mutex);

  if (x != 0) {
    printf("BOOM! counter=%d\n", x);
  } else {
    printf("OK counter=%d\n", x);
  }
}

void *producer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    pthread_mutex_lock(&mutex);
    while (x == MAX) {
      pthread_cond_wait(&empty, &mutex);
    }
    if (x < MAX) {
      x++;
    }
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    pthread_cond_signal(&fill);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    pthread_mutex_lock(&mutex);
    while (x == 0) {
      pthread_cond_wait(&fill, &mutex);
    }
    if (x > 0) {
      x--;
    }
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}