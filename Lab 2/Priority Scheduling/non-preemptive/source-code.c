#include <stdio.h>
//non-preemptive
void priorityScheduling(int n, int at[], int bt[], int pr[], int ct[], int tat[], int wt[], int rt[]) {
    int completed = 0, time = 0, min_priority, highest_priority;
    int flag[n];
    for (int i = 0; i < n; i++) {
        flag[i] = 0;
    }
    while (completed < n) {
        min_priority = 9999;
        highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && flag[i] == 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                highest_priority = i;
            }
        }
        if (highest_priority == -1) {
            time++;
            continue;
        }
        time += bt[highest_priority];
        flag[highest_priority] = 1;
        ct[highest_priority] = time;
        tat[highest_priority] = ct[highest_priority] - at[highest_priority];
        wt[highest_priority] = tat[highest_priority] - bt[highest_priority];
        rt[highest_priority] = wt[highest_priority];
        completed++;
    }
}

void displayTable(int n, int at[], int bt[], int pr[], int ct[], int tat[], int wt[], int rt[]) {
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n], rt[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &pr[i]);
    }
    priorityScheduling(n, at, bt, pr, ct, tat, wt, rt);
    displayTable(n, at, bt, pr, ct, tat, wt, rt);
    return 0;
}
