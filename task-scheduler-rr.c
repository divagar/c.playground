#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define TOTAL_TASK 3 // TOtal number of tasks
#define TASK_SLICE 1 // Time allocate by task in a go

typedef struct
{
    int task_id;
    int brust_time;
    int remaining_time
} TASK;

// simple round robin based task scheduler
void execute_task(TASK *task)
{
    printf("Task %d under execution, with task remaining time %d\n", task->task_id, task->remaining_time);
    if (task->remaining_time > TASK_SLICE)
    {
        sleep(TASK_SLICE); // stimulate a task execution by sleep
        task->remaining_time -= TASK_SLICE;
    }
    else
    {
        sleep(task->remaining_time);
        task->remaining_time = 0;
        printf("Task %d completed execution.\n", task->task_id);
    }
}

int main()
{
    TASK task[TOTAL_TASK] = {
        {0, 5, 5},
        {1, 10, 10},
        {2, 3, 3}};

    int all_task_completed = 1;
    do
    {
        all_task_completed = 1;

        for (int t = 0; t < TOTAL_TASK; t++)
        {
            if (task[t].remaining_time >= TASK_SLICE)
            {
                execute_task(&task[t]);
                all_task_completed = 0;
            }
        }
    } while (!all_task_completed);

    printf("All task completed execution.\n");
    return 0;
}