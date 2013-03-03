#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    <string.h>
#include    <pthread.h>

void *thread_function(void *arg);

int running_now = 1;

int main(int argc, char *argv[])
{
	int res;
	pthread_t a_thread;
	int print_count1 = 0;

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread creation failed.\n");
		exit(EXIT_FAILURE);
	}
	
	while (print_count1++ < 20) {
		if (running_now == 1) {
			printf("1\n");
			running_now = 2;
		}
		else
			sleep(1);
	}
	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread, NULL);
	if (res != 0) {
		perror("Thread join failed.\n");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined.\n");
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	int print_count2 = 0;
	printf("thread_function is running.\n");
	while (print_count2++ < 20) {
		if (running_now == 2) {
			printf("2\n");
			running_now = 1;
		}
		else
			sleep(1);
	}
	pthread_exit("Thank you for the CPU time.");
}
