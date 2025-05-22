#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int main() {
    int finish[P] = {0};
    int safeSeq[P];
    int work[R];

    // Maximum need matrix
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Allocation matrix
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Available resources
    int available[R] = {3, 3, 2};

    // Calculate need matrix = max - allocation
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Copy available to work
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int r = 0; r < R; r++) {
                        work[r] += allocation[p][r];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            break; // No process could finish in this round
        }
    }

    if (count == P) {
        printf("System is in a SAFE state.\nSafe sequence is: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is in an UNSAFE (potential deadlock) state.\n");
    }

    return 0;
}