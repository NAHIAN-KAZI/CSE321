#include <stdio.h>
#include <unistd.h>

int main() {
    int thread_count = 1;

    for (int i = 0; i < 5; i++) {
        printf("thread-%d running\n", thread_count);
        sleep(2); 
        printf("thread-%d closed\n", thread_count);
        thread_count++;
    }

    return 0;
}