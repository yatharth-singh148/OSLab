#include <stdio.h>

int x = 1, mutex = 1, full = 0, empty = 3;
void wait(int *S) 
{
    (*S)--;
}

void signal(int *S) 
{
    (*S)++; 
}
void producer() 
{
    wait(&mutex);
    if (empty > 0) 
    {
        wait(&empty);
        signal(&full);
        printf("Item produced: %d\n", x++);
    } else {
        printf("Buffer is Full\n");
    }
    signal(&mutex);
}
void consumer() {
    wait(&mutex);
    if (full > 0) {
        wait(&full);
        signal(&empty);
        printf("Item Consumed: %d\n", --x);
    } else {
        printf("Buffer is Empty\n");
    }
    signal(&mutex);
}

int main() {
    int ch;
    printf("1. Produce\n2. Consume\n3. Exit\n");
    while (1) {
        printf("Enter Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: producer(); break;
            case 2: consumer(); break;
            default: return 0;
    }
}
}
