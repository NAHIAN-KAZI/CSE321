#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* execute_task(void* args);
int current_task = 0;
int main() {
	for (int i = 0; i < 5; i++) {
		pthread_t thread;
		pthread_create(&thread, NULL, execute_task, NULL);
		pthread_join(thread, NULL);
		current_task++;
	}
	return 0;
}
void* execute_task(void* args) {
	int total_tasks = 5;
	for (int i = 1; i <= 5; i++) {
		printf("task %d prints %d\n", current_task, (current_task * total_tasks) + i);
	}
}