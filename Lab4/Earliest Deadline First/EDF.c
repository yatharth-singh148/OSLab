#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline;
    int executed;
} Task;

int compare_tasks(const void *a, const void *b) {
    return ((Task *)a)->deadline - ((Task *)b)->deadline;
}

void earliest_deadline_first_scheduling(Task tasks[], int num_tasks, int total_time) {
    printf("Time\t");
    for (int i = 0; i < num_tasks; i++)
        printf("Task %d\t", tasks[i].id);
    printf("\n");
    for (int current_time = 0; current_time < total_time; current_time++) {
        printf("%d\t", current_time);
        int executed_task = -1;

        for (int i = 0; i < num_tasks; i++) {
            if (current_time % tasks[i].period == 0) {
                tasks[i].deadline = current_time + tasks[i].period;
                tasks[i].executed = 0;
            }
        }
        qsort(tasks, num_tasks, sizeof(Task), compare_tasks);

        for (int i = 0; i < num_tasks; i++) {
            if (current_time < tasks[i].deadline && tasks[i].executed < tasks[i].execution_time) {
                executed_task = i;
                tasks[i].executed++;
                break;
            }
        }
        if (executed_task != -1) {
            for (int i = 0; i < num_tasks; i++) {
                if (i == executed_task) {
                    printf("Exec\t");
                } else {
                    printf("\t");
                }
            }
        } else {
            for (int i = 0; i < num_tasks; i++) {
                printf("\t");
            }
        }
        printf("\n");
    }
}

int main() {
    Task tasks[] = {
        {1, 20, 3, 20, 0},
        {2, 5, 2, 5, 0},
        {3, 10, 2, 10, 0}                                                                     //task
    };

    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);
    int total_time = 20;

    earliest_deadline_first_scheduling(tasks, num_tasks, total_time);
    return 0;
}
