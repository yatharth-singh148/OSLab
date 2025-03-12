#include <stdio.h>
void preemptiveSJF(int n, int at[], int bt[], int ct[], int tat[], int wt[], int rt[])
{
    int remaining_bt[n];
    int completed = 0, time = 0, min_bt, shortest;
    int flag[n];
    for (int i = 0; i < n; i++)
    {
        remaining_bt[i] = bt[i];
        flag[i] = 0;
    }

    while (completed < n)
    {
        min_bt = 9999;
        shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt && flag[i] == 0)
            {
                min_bt = remaining_bt[i];
                shortest = i;
            }
        }
        if (shortest == -1)
        {
            time++;
            continue;
        }
        remaining_bt[shortest]--;
        if (remaining_bt[shortest] == 0)
        {
            completed++;
            flag[shortest] = 1;
            ct[shortest] = time + 1;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            rt[shortest] = wt[shortest];
        }
        time++;
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
    preemptiveSJF(n, at, bt, ct, tat, wt, rt);
    displayTable(n, at, bt, ct, tat, wt, rt);

    return 0;
}
