#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2

void* consumer(int* id);
void* producer(int* id);

char buffer[BUFLEN];
char source[BUFLEN] = "abcdef";
int pCount = 0, cCount = 0;
int buflen;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = { 0, 1 };

int main() {
    int i;
    pthread_t thread[NUMTHREAD];

    buflen = strlen(source);

    
    pthread_create(&thread[0], NULL, (void*)producer, (void*)&thread_id[0]);
    pthread_create(&thread[1], NULL, (void*)consumer, (void*)&thread_id[1]);
    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void* producer(int* id) {
    int i;
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (pCount == BUFLEN) {
            pthread_cond_wait(&full, &count_mutex);
        }
        buffer[pCount++] = source[i];
        printf("%d produced %c by Thread %d\n", pCount, buffer[pCount - 1], *id);
        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
    }
    return NULL;
}

void* consumer(int* id) {
    int i;
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (cCount == 0) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }
        printf("%d consumed %c by Thread %d\n", cCount, buffer[cCount - 1], *id);
        cCount--;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
    }
    return NULL;
}