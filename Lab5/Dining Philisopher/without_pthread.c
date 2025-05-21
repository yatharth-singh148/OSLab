#include <stdio.h>

#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

const char* stateNames[] = {"Thinking", "Hungry", "Eating"};

int state[N];  // State of each philosopher

int left(int i) {
    return (i + N - 1) % N;
}

int right(int i) {
    return (i + 1) % N;
}

void printStates(int round) {
    printf("\nRound %d:\n", round);
    for (int i = 0; i < N; i++) {
        printf("Philosopher %d is %s\n", i + 1, stateNames[state[i]]);
    }
}

void simulateDining(int rounds) {
    // Initialize all philosophers to THINKING
    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
    }

    for (int r = 1; r <= rounds; r++) {
        for (int i = 0; i < N; i++) {
            if (state[i] == THINKING) {
                state[i] = HUNGRY;
            } else if (state[i] == HUNGRY) {
                if (state[left(i)] != EATING && state[right(i)] != EATING) {
                    state[i] = EATING;
                }
            } else if (state[i] == EATING) {
                state[i] = THINKING;
            }
        }
        printStates(r);
    }
}

int main() {
    int rounds;
    printf("Enter number of simulation rounds: ");
    scanf("%d", &rounds);

    simulateDining(rounds);
    return 0;
}
