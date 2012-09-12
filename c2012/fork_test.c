#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * file: fork_test.c
 * a sample to test fork.
 */

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i<2; i++){
		fork();
		/* printf("-"); */
		printf("-\n");
	}
	return 0;
}
