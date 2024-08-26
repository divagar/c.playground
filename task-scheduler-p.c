#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct
{
    int id;
    int burst_time;
    int remaining_time;
    int priority;
} TASK;

#define TASK_TOTAL 5
#define TASK_SLICE_TIME 1

int find_priority_task(TASK task[])
{
    //printf("Finding the high priority task. Total task: %d\n", TASK_TOTAL);
    int priority_task_index = -1;
    for (int t = 0; t < TASK_TOTAL; t++)
    {
        if (task[t].remaining_time >= TASK_SLICE_TIME)
        {
            if (priority_task_index == -1 || task[t].priority < task[priority_task_index].priority)
                priority_task_index = t;
        }
    }
    return priority_task_index;
}

void execute_task(TASK *task)
{
    // printf("About to executed task #%d\n", task->id);
    if (task->remaining_time > TASK_SLICE_TIME)
    {
        printf("Task #%d is executing!\n", task->id);
        sleep(TASK_SLICE_TIME); // stimulate the task schedule using sleep
        task->remaining_time -= TASK_SLICE_TIME;
    }
    else
    {
        sleep(task->remaining_time); // stimulate the task schedule using sleep
        task->remaining_time = 0;
        printf("*** Task #%d is completed! ***\n", task->id);
    }
}

int main()
{
    TASK task[TASK_TOTAL] = {
        {0, 5, 5, 1},
        {1, 10, 10, 0},
        {2, 7, 7, 2},
        {4, 12, 12, 0},
        {5, 5, 5, 1}};

    int all_task_completed = 1;
    do
    {
        all_task_completed = 1;
        for (int t = 0; t < TASK_TOTAL; t++)
        {
            if (task[t].remaining_time != 0)
            {
                int priority_index = find_priority_task(task);
                //printf("priority_index -> %d\n", priority_index);
                execute_task(&task[priority_index]);
                all_task_completed = 0;
            }
        }
    } while (!all_task_completed);

    printf("All task completed execution\n");
    return 0;
}