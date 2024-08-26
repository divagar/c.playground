#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define THREADS 5
#define ITEMS 3

typedef struct
{
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count
} fifo_buffer_t;

fifo_buffer_t fifo_buf = {
    .in = 0,
    .out = 0,
    .count = 0};

sem_t empty;
sem_t full;

void *producer_executor(void *args)
{
    int threadId = *((int *)args);

    for (int i = 0; i < ITEMS; i++)
    {
        int item = 100 + i;
        sem_wait(&empty);
        printf("Thread #%d producing %d\n", threadId, item);
        fifo_buf.buffer[fifo_buf.in] = item;
        fifo_buf.in = (fifo_buf.in + 1) % BUFFER_SIZE;
        fifo_buf.count += 1;
        sem_post(&full);
    }
}

void *consumer_executor(void *args)
{
    int threadId = *((int *)args);

    for (int i = 0; i < ITEMS; i++)
    {
        int item;
        sem_wait(&full);
        item = fifo_buf.buffer[fifo_buf.out];
        printf("Thread #%d consume %d\n", threadId, item);
        fifo_buf.out = (fifo_buf.out + 1) % BUFFER_SIZE;
        fifo_buf.count -= 1;
        sem_post(&empty);
    }
}

int main()
{
    pthread_t pThreads[THREADS];
    pthread_t cThreads[THREADS];
    int theardIds[THREADS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for (int t = 0; t < THREADS; t++)
    {
        theardIds[t] = t + 1;
        pthread_create(&pThreads[t], NULL, producer_executor, &theardIds[t]);
        pthread_create(&cThreads[t], NULL, consumer_executor, &theardIds[t]);
    }

    for (int t = 0; t < THREADS; t++)
    {
        pthread_join(pThreads[t], NULL);
        pthread_join(cThreads[t], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}