#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completed;
} Process;

Process rr1[MAX], rr2[MAX], fcfs[MAX];
int rr1_count = 0, rr2_count = 0, fcfs_count = 0;
void add_fcfs(Process p) {
    fcfs[fcfs_count++] = p;
}
void add_rr1(Process p) {
    rr1[rr1_count++] = p;
}
void add_rr2(Process p) {
    rr2[rr2_count++] = p;
}
void round_robin(Process queue[], int n, int quantum) {
    int time = 0;
    int i, all_done;
    
    while (1) {
        all_done = 1;
        
        for (i = 0; i < n; i++) {
            if (queue[i].completed == 0) {
                all_done = 0;
                if (queue[i].remaining_time > quantum) {
                    queue[i].remaining_time -= quantum;
                    time += quantum;
                    printf("Time %d: Process %d executed for %d time units\n", time, queue[i].pid, quantum);
                } else {
                    time += queue[i].remaining_time;
                    printf("Time %d: Process %d executed for %d time units and completed\n", time, queue[i].pid, queue[i].remaining_time);
                    queue[i].remaining_time = 0;
                    queue[i].completed = 1;
                }
            }
        }
        if (all_done == 1) {
            break;
        }
    }
}
void fcfs() {
    int time = 0;
    int i;
    
    for (i = 0; i < fcfs_count; i++) {
        time += fcfs[i].burst_time;
        printf("Time %d: Process %d executed for %d time units (FCFS)\n", time - fcfs[i].burst_time, fcfs[i].pid, fcfs[i].burst_time);
    }
}

int main() {
    int quantum_rr1, quantum_rr2;
    int num_processes;
    printf("Enter time quantum for RR1 queue: ");
    scanf("%d", &quantum_rr1);
    
    printf("Enter time quantum for RR2 queue: ");
    scanf("%d", &quantum_rr2);
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    for (int i = 0; i < num_processes; i++) {
        Process p;
        printf("\nEnter details for Process %d\n", i + 1);
        printf("Enter Process ID: ");
        scanf("%d", &p.pid);
        printf("Enter Burst Time: ");
        scanf("%d", &p.burst_time);
        printf("Enter Arrival Time (for FCFS): ");
        scanf("%d", &p.arrival_time);
        if (i % 2 == 0) {
            add_rr1(p);
        } else if (i % 3 == 0) {
            add_rr2(p);
        } else {
            add_fcfs(p);
        }
    }
    printf("\nProcesses in RR1 queue:\n");
    for (int i = 0; i < rr1_count; i++) {
        printf("Process %d, Burst Time: %d\n", rr1[i].pid, rr1[i].burst_time);
        rr1[i].remaining_time = rr1[i].burst_time;
    }

    printf("\nProcesses in RR2 queue:\n");
    for (int i = 0; i < rr2_count; i++) {
        printf("Process %d, Burst Time: %d\n", rr2[i].pid, rr2[i].burst_time);
        rr2[i].remaining_time = rr2[i].burst_time;
    }

    printf("\nProcesses in FCFS queue:\n");
    for (int i = 0; i < fcfs_count; i++) {
        printf("Process %d, Burst Time: %d\n", fcfs[i].pid, fcfs[i].burst_time);
    }
    printf("\nRound Robin Scheduling (Queue 1):\n");
    round_robin(rr1, rr1_count, quantum_rr1);
    
    printf("\nRound Robin Scheduling (Queue 2):\n");
    round_robin(rr2, rr2_count, quantum_rr2);
    printf("\nFCFS Scheduling:\n");
    fcfs();
    
    return 0;
}
