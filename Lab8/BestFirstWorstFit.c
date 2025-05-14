#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int pid, burst_time, period, deadline, remaining_time;
} Process;
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
void rate_monotonic_scheduling(Process processes[], int n) {
    int hyperperiod = processes[0].period;
    for (int i = 1; i < n; i++)
        hyperperiod = lcm(hyperperiod, processes[i].period);
    float utilization = 0;
    for (int i = 0; i < n; i++)
        utilization += (float)processes[i].burst_time / processes[i].period;
    float threshold = n * (pow(2.0, 1.0 / n) - 1);
    printf("\nRate Monotonic Scheduling:\nPID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].period);

    printf("\n%.6f <= %.6f => %s\n", utilization, threshold, (utilization <= threshold) ? "true" : "false");
}
void earliest_deadline_first_scheduling(Process processes[], int n) {
    printf("\nEarliest Deadline Scheduling:\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].deadline, processes[i].period);

    printf("\nScheduling occurs for %d ms\n", processes[0].burst_time * n);
    for (int time = 0; time < processes[0].burst_time * n; time++)
        printf("%dms : Task %d is running.\n", time, processes[0].pid);
}
int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        scanf("%d", &processes[i].burst_time);
    }
    printf("Enter 1 for Rate Monotonic Scheduling or 2 for Earliest Deadline First: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter the time periods:\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &processes[i].period);
        rate_monotonic_scheduling(processes, n);
    } else if (choice == 2) {
        printf("Enter the deadlines:\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &processes[i].deadline);

        printf("Enter the time periods:\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &processes[i].period);

        earliest_deadline_first_scheduling(processes, n);
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}
