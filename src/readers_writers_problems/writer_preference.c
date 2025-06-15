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
#define ITER 10000

void *readers(void *arg);
void *writers(void *arg);

sem_t x, y, z, m, wsem, rsem;
int readercount = 0, writercount = 0;

int main() {
  pthread_t tid1, tid2;
  sem_init(&m, 0, 1);
  sem_init(&x, 0, 1);
  sem_init(&y, 0, 1);
  sem_init(&z, 0, 1);
  sem_init(&wsem, 0, 1);
  sem_init(&rsem, 0, 1);

  pthread_create(&tid1, NULL, readers, NULL);
  pthread_create(&tid2, NULL, writers, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  sem_destroy(&rsem);
  sem_destroy(&wsem);
  sem_destroy(&z);
  sem_destroy(&y);
  sem_destroy(&x);
  sem_destroy(&m);
}

void *readers(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&z);
    sem_wait(&rsem);
    sem_wait(&x);
    readercount++;
    if (readercount == 1) {
      sem_wait(&wsem);
    }
    sem_post(&x);
    sem_post(&rsem);
    sem_post(&z);

    printf("Reader!\n");

    sem_wait(&x);
    readercount--;
    if (readercount == 0) {
      sem_post(&wsem);
    }
    sem_post(&x);
  }
  return NULL;
}

void *writers(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&y);
    writercount++;
    if (writercount == 1) {
      sem_wait(&rsem);
    }
    sem_post(&y);

    sem_wait(&wsem);
    printf("Writer!\n");
    sem_post(&wsem);

    sem_wait(&y);
    writercount--;
    if (writercount == 0) {
      sem_post(&rsem);
    }
    sem_post(&y);
  }
  return NULL;
}