#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid;
    struct shared *shm;
    int pid;
    int pipe_fd[2];

    
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);

    
    pipe(pipe_fd);

    
    char selection[100];
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    scanf("%s", selection);
    strcpy(shm->sel, selection);
    shm->b = 1000;
    printf("Your selection: %s\n", shm->sel);

    
    pid = fork();
    if (pid == 0) {
        
        int amount;
        char buffer[100];

        if (strcmp(shm->sel, "a") == 0) {
            printf("Enter amount to be added: ");
            scanf("%d", &amount);
            if (amount > 0) {
                shm->b += amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition: %d\n", shm->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "w") == 0) {
            printf("Enter amount to be withdrawn: ");
            scanf("%d", &amount);
            if (amount > 0 && amount < shm->b) {
                shm->b -= amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal: %d\n", shm->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "c") == 0) {
            printf("Your current balance is: %d\n", shm->b);
        } else {
            printf("Invalid selection\n");
        }

        
        sprintf(buffer, "Thank you for using");
        write(pipe_fd[1], buffer, strlen(buffer) + 1);
        exit(0);
    }

    
    wait(NULL); 
    char buffer[100];
    read(pipe_fd[0], buffer, sizeof(buffer));
    printf("%s\n", buffer);
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}