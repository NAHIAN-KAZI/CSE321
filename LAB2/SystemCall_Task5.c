#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t parent_pid, child_pid, grandchild_pid;
    parent_pid = getpid();

    printf("Parent process ID: %d\n", parent_pid);

    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (child_pid == 0) {

        printf("Child process ID: %d\n", getpid());

        grandchild_pid = fork();
        if (grandchild_pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
        else if (grandchild_pid == 0) {

            printf("Grandchild process ID: %d\n", getpid());
        }
        else {

            wait(NULL);

            grandchild_pid = fork();
            if (grandchild_pid < 0) {
                fprintf(stderr, "Fork failed\n");
                return 1;
            }
            else if (grandchild_pid == 0) {

                printf("Grandchild process ID: %d\n", getpid());
            }
            else {

                wait(NULL);

                grandchild_pid = fork();
                if (grandchild_pid < 0) {
                    fprintf(stderr, "Fork failed\n");
                    return 1;
                }
                else if (grandchild_pid == 0) {

                    printf("Grandchild process ID: %d\n", getpid());
                }
                else {

                    wait(NULL);
                }
            }
        }
    }
    else {

        wait(NULL);
    }

    return 0;
}