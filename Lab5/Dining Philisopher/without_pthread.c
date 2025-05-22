#include <stdio.h>
#include <unistd.h>

#define N 3  // Number of philosophers

int forks[N] = {1, 1, 1};  // 1 means fork is available

void pick_up_forks(int id) {
    if (forks[id] && forks[(id + 1) % N]) {
        forks[id] = 0;
        forks[(id + 1) % N] = 0;
        printf("Philosopher %d picked up forks %d and %d.\n", id, id, (id + 1) % N);
    } else {
        printf("Philosopher %d is waiting for forks.\n", id);
    }
}

void put_down_forks(int id) {
    forks[id] = 1;
    forks[(id + 1) % N] = 1;
    printf("Philosopher %d put down forks %d and %d.\n", id, id, (id + 1) % N);
}

void simulate_philosopher(int id) {
    printf("Philosopher %d is thinking...\n", id);
    sleep(1);

    pick_up_forks(id);

    if (forks[id] == 0 && forks[(id + 1) % N] == 0) {
        printf("Philosopher %d is eating...\n", id);
        sleep(2);
        put_down_forks(id);
    }
    sleep(1);
}

int main() {
    while (1) {
        for (int i = 0; i < N; i++) {
            simulate_philosopher(i);
        }
    }
    return 0;
}