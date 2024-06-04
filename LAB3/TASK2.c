#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct msg {
    long int type;
    char txt[6];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, IPC_CREAT | 0666);

    char workspace[100];
    struct msg message;

    printf("Please enter the workspace name: ");
    scanf("%s", workspace);

    if (strcmp(workspace, "cse321") == 0) {
        strcpy(message.txt, workspace);
        message.type = 1;
        printf("Workspace name sent to otp generator from log in: %s\n", message.txt);
        msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);

        pid_t pid = fork();
        if (pid == 0) {
            
            struct msg received_msg, send_msg;

            
            msgrcv(msgid, &received_msg, sizeof(received_msg) - sizeof(long), 1, 0);
            printf("OTP generator received workspace name from log in: %s\n", received_msg.txt);

            
            pid_t otp = getpid();
            sprintf(send_msg.txt, "%d", otp);
            send_msg.type = 2;
            printf("OTP sent to log in from OTP generator: %s\n", send_msg.txt);
            msgsnd(msgid, &send_msg, sizeof(send_msg) - sizeof(long), 0);

            
            pid_t mail_pid = fork();
            if (mail_pid == 0) {
                
                struct msg received_msg, send_msg;

                
                msgrcv(msgid, &received_msg, sizeof(received_msg) - sizeof(long), 3, 0);
                printf("Mail received OTP from OTP generator: %s\n", received_msg.txt);

                
                strcpy(send_msg.txt, received_msg.txt);
                send_msg.type = 4;
                printf("OTP sent to log in from mail: %s\n", send_msg.txt);
                msgsnd(msgid, &send_msg, sizeof(send_msg) - sizeof(long), 0);

                exit(0); 
            }

            
            send_msg.type = 3;
            msgsnd(msgid, &send_msg, sizeof(send_msg) - sizeof(long), 0);
            printf("OTP sent to mail from OTP generator: %s\n", send_msg.txt);

            exit(0); 
        }

        
        wait(NULL); 

        struct msg received_msg;

        
        msgrcv(msgid, &received_msg, sizeof(received_msg) - sizeof(long), 2, 0);
        printf("Log in received OTP from OTP generator: %s\n", received_msg.txt);
        char otp_generator[6];
        strcpy(otp_generator, received_msg.txt);

        
        msgrcv(msgid, &received_msg, sizeof(received_msg) - sizeof(long), 4, 0);
        printf("Log in received OTP from mail: %s\n", received_msg.txt);

        
        if (strcmp(otp_generator, received_msg.txt) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        
        msgctl(msgid, IPC_RMID, NULL);
    } else {
        printf("Invalid workspace name\n");
    }

    return 0;
}