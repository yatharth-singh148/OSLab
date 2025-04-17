#include <stdio.h>
#include <stdlib.h>
int condition(int **need, int *work, int i, int m)
{
    for (int j = 0; j < m; j++)
    {
        if (need[i][j] > work[j])
            return 0;
    }
    return 1;
}
int safety(int m, int n, int **allocated, int **max, int *available, int *sequence)
{
    // Need Matrix
    int **need = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        need[i] = (int*) malloc(m * sizeof(int));
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    // Work array
    int *work = (int*) malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    // Finish array
    int *finish = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int safeIndex = 0;
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i] && condition(need, work, i, m))
            {
                for (int j = 0; j < m; j++)
                {
                    work[j] += allocated[i][j];
                }
                finish[i] = 1;
                sequence[safeIndex++] = i;
                changed = 1;
            }
        }
    } while (changed);

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n, m;
    printf("Enter number of processes and resources (n x m order): ");
    scanf("%d",&n);
    scanf("%d",&m);
    // Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    int **allocated = (int **) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        allocated[i] = (int*) malloc(m * sizeof(int));
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocated[i][j]);
        }
    }

    // Max Matrix
    printf("Enter Max Matrix:\n");
    int **max = (int **) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        max[i] = (int*) malloc(m * sizeof(int));
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    // Available Matrix
    printf("Enter Available matrix:\n");
    int *available = (int *) malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    // Sequence Matrix
    int *sequence = (int *) malloc(n * sizeof(int));

    int safe = safety(m, n, allocated, max, available, sequence);
    if (safe)
    {
        printf("System is in a Safe State.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d\t", sequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is not in a Safe State.\n");
    }
    return 0;
}
