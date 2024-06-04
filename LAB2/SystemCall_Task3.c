#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2, child3;
    int total_processes = 1;

    child1 = fork();
    if (child1 != 0) {
        total_processes++;
    } else {
        if (child1 % 2 != 0) {
            total_processes++;
            fork();
        }
    }

    child2 = fork();
    if (child2 != 0) {
        total_processes++;
    } else {
        if (child2 % 2 != 0) {
            total_processes++;
            fork();
        }
    }

    child3 = fork();
    if (child3 != 0) {
        total_processes++;
    } else {
        if (child3 % 2 != 0) {
            total_processes++;
            fork();
        }
    }

    while (wait(NULL) > 0);

    if (child1 > 0 && child2 > 0 && child3 > 0) {
        printf("Value of child1: %d\n", child1);
        printf("Value of child2: %d\n", child2);
        printf("Value of child3: %d\n", child3);
        printf("Total number of processes created: %d\n", total_processes);
    }

    return 0;
}