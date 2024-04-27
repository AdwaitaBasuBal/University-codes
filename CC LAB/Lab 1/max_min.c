#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 100

typedef struct {
    int task_id;
    int execution_time;
} Task;

void max_min_scheduling(Task tasks[], int num_tasks) {
    int i, j;
    int max_time, max_task_id;

    printf("Max-min Scheduling:\n");

    for (i = 0; i < num_tasks; i++) {
        max_time = -1;
        max_task_id = -1;

        for (j = 0; j < num_tasks; j++) {
            if (tasks[j].execution_time > max_time) {
                max_time = tasks[j].execution_time;
                max_task_id = j;
            }
        }

        printf("Task %d with execution time %d is assigned\n", tasks[max_task_id].task_id, tasks[max_task_id].execution_time);
        tasks[max_task_id].execution_time = -1; // Mark task as assigned
    }
}

void min_min_scheduling(Task tasks[], int num_tasks) {
    int i, j;
    int min_time, min_task_id;

    printf("\nMin-min Scheduling:\n");

    for (i = 0; i < num_tasks; i++) {
        min_time = __INT_MAX__;
        min_task_id = -1;

        for (j = 0; j < num_tasks; j++) {
            if (tasks[j].execution_time != -1 && tasks[j].execution_time < min_time) {
                min_time = tasks[j].execution_time;
                min_task_id = j;
            }
        }

        printf("Task %d with execution time %d is assigned\n", tasks[min_task_id].task_id, tasks[min_task_id].execution_time);
        tasks[min_task_id].execution_time = -1; // Mark task as assigned
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int num_tasks, i;

    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    printf("Enter the execution time for each task:\n");
    for (i = 0; i < num_tasks; i++) {
        printf("Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        tasks[i].task_id = i + 1;
    }

    max_min_scheduling(tasks, num_tasks);
    min_min_scheduling(tasks, num_tasks);

    return 0;
}
