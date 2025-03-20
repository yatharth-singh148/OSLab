#include <stdio.h>

struct Process {
    int id, arrivalTime, burstTime, remainingTime, priority;
    int waitingTime, turnaroundTime, completionTime;
};
int findHighestPriority(struct Process p[], int n, int currentTime) {
    int highest = -1;
    int highestPriority = 1e9;
    
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
            if (p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                highest = i;
            }
        }
    }
    return highest;
}

void priorityScheduling(struct Process p[], int n) {
    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].burstTime;
    }
    while (completed < n) {
        int idx = findHighestPriority(p, n, currentTime);

        if (idx == -1) {
            currentTime++;
            continue;
        }

        p[idx].remainingTime--;
        currentTime++;
        if (p[idx].remainingTime == 0) {
            completed++;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalWaitingTime += p[idx].waitingTime;
            totalTurnaroundTime += p[idx].turnaroundTime;
        }
    }
    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].priority, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct Process p[n];

    printf("Enter Arrival Time, Burst Time, and Priority (lower number = higher priority) for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
    }
    priorityScheduling(p, n);
    return 0;
}
