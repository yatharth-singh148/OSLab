#include <stdio.h>
#define TIME_QUANTUM 2
typedef struct {
    int pid, burst_time, arrival_time, queue;
    int waiting_time, turnaround_time, response_time, remaining_time;
} Process;
void sort_by_arrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
void round_robin(Process p[], int n, int *time) {
    int done, i;
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                done = 0;
                if (p[i].remaining_time > TIME_QUANTUM) {
                    *time += TIME_QUANTUM;
                    p[i].remaining_time -= TIME_QUANTUM;
                } else {
                    *time += p[i].remaining_time;
                    p[i].waiting_time = *time - p[i].arrival_time - p[i].burst_time;
                    p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
                    p[i].response_time = p[i].waiting_time;
                    p[i].remaining_time = 0;
                }
            }
        }
    } while (!done);
}
void fcfs(Process p[], int n, int *time) {
    for (int i = 0; i < n; i++) {
        if (*time < p[i].arrival_time)
            *time = p[i].arrival_time;
        p[i].waiting_time = *time - p[i].arrival_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].response_time = p[i].waiting_time;
        *time += p[i].burst_time;
    }
}
int main() {
    int n, i, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n], system_processes[n], user_processes[n];
    int sys_count = 0, user_count = 0;

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].burst_time, &p[i].arrival_time, &p[i].queue);
        p[i].remaining_time = p[i].burst_time;

        if (p[i].queue == 0)
            system_processes[sys_count++] = p[i];
        else
            user_processes[user_count++] = p[i];
    }
    sort_by_arrival(system_processes, sys_count);
    sort_by_arrival(user_processes, user_count);
    printf("\nQueue 1 is System Process\nQueue 2 is User Process\n");
    round_robin(system_processes, sys_count, &time);
    fcfs(user_processes, user_count, &time);
    Process final_list[n];
    int index = 0;
    for (i = 0; i < sys_count; i++)
        final_list[index++] = system_processes[i];
    for (i = 0; i < user_count; i++)
        final_list[index++] = user_processes[i];

    printf("\nProcess\tWaiting Time\tTurn Around Time\tResponse Time\n");
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t\t%d\n", final_list[i].pid, final_list[i].waiting_time, final_list[i].turnaround_time, final_list[i].response_time);
        avg_wt += final_list[i].waiting_time;
        avg_tat += final_list[i].turnaround_time;
        avg_rt += final_list[i].response_time;
    }
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    float throughput = (float)n / time;
    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turn Around Time: %.2f", avg_tat);
    printf("\nAverage Response Time: %.2f", avg_rt);
    printf("\nThroughput: %.2f", throughput);
    return 0;
}
