#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define No_OF_THREADS 5

sem_t my_sem;

int counter = 0;

void *thread_executor(void *args)
{
    int thread_id = *((int *)args);
    printf("Thread #%d under execution.\n", thread_id);

    sem_wait(&my_sem);

    int local_counter = counter;

    sleep(1);
    local_counter++;

    counter = local_counter;

    printf("Thread #%d completed execution. counter = %d\n", thread_id, counter);

    sem_post(&my_sem);

    return NULL;
}

int main()
{
    pthread_t my_threads[No_OF_THREADS];
    int threads_ids[No_OF_THREADS];

    sem_init(&my_sem, 0, 1);

    for (int t = 0; t < No_OF_THREADS; t++)
    {
        threads_ids[t] = t + 1;
        pthread_create(&my_threads[t], NULL, thread_executor, &threads_ids[t]);
    }

    for (int t = 0; t < No_OF_THREADS; t++)
    {
        pthread_join(my_threads[t], NULL);
    }

    sem_destroy(&my_sem);

    printf("All thread completed execution. counter = %d\n", counter);

    return 0;
}