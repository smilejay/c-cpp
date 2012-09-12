#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * file: clean_shm.c
 * to remove/clean shm by shmid.
 * need a paramter for exact $shmid.
 * You can get $shmid from 'ipcs -m' command line.
 */


int main(int argc, char** argv)
{
	int shmid=0;
	int i=0;
	if ( argc <= 1 ) {
		printf("Need 1 parameter.\n",argv[0]);
		printf("%s decimal_shmid\n",argv[0]);
		return -1;
	}
        key_t key = atol(argv[1]);
	
	for(i=0;i<100;i++) {
		shmid=shmget(key,1024,0666);
		shmctl(shmid,IPC_RMID,0);
		key++;
	}
	return 0;
}
