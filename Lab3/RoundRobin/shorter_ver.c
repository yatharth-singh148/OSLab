#include <stdio.h>

struct Process {
    int id;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int completed;
};

int main() {
    int n, i, time = 0, remain;
    int quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time for P[%d]: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for P[%d]: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    remain = n;
    int done;

    while (remain != 0) {
        done = 1;
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                done = 0;
                if (p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt - p[i].at;
                    p[i].rt = 0;
                    p[i].tat = p[i].wt + p[i].bt;
                    p[i].completed = 1;
                    remain--;
                }
            }
        }

        // If no process was ready, increment time
        if (done)
            time++;
    }

    // Display results
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    return 0;
}