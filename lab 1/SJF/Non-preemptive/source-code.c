#include <stdio.h>
void nonPreemptiveSJF(int n, int at[], int bt[], int ct[], int tat[], int wt[], int rt[])
{
    int completed = 0, time = 0, min_bt, shortest, finish_time;
    int remaining_bt[n];
    for (int i = 0; i < n; i++)
    {
        remaining_bt[i] = bt[i];
    }

    while (completed < n)
    {
        min_bt = 9999;
        shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && remaining_bt[i] > 0 && bt[i] < min_bt)
            {
                min_bt = bt[i];
                shortest = i;
            }
        }
        if (shortest == -1)
        {
            time++;
            continue;
        }
        time += bt[shortest];
        remaining_bt[shortest] = 0;
        completed++;
        ct[shortest] = time;
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        rt[shortest] = wt[shortest];
    }
}

void displayTable(int n, int at[], int bt[], int ct[], int tat[], int wt[], int rt[])
{
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }
    nonPreemptiveSJF(n, at, bt, ct, tat, wt, rt);
    displayTable(n, at, bt, ct, tat, wt, rt);
    return 0;
}
