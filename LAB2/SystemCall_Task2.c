#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t parent_id, child_id, grandchild_id;
    
    child_id = fork();

    if (child_id < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } 
    else if (child_id == 0) {
        grandchild_id = fork();

        if (grandchild_id < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } 
        else if (grandchild_id == 0) {
            printf("I am grandchild\n");
        } 
        else {
            
            int status;
            wait(&status);
            printf("I am child\n");
        }
    } else {
        
        int status;
        wait(&status);
        printf("I am parent\n");
    }

    return 0;
}
