#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>

/* Create two processes A and B. 
 * A creates a shared memory segment. 
 * A then keeps reading strings from the standard input and places whatever it reads in the shared memory segment (replacing previous data). 
 * Process B, on each run, reads the data from the shared memory segment and counts the number of vowels. 
 * Process A, upon receiving a SIGINT, deletes the shared memory segment.
 */

struct shared_mem {
	char string[256];
};

int A2B, shmid;
struct shared_mem* m;

void f(int sig){
	close(A2B);
	shmdt(m);
	shmctl(shmid, IPC_RMID, 0);
	printf("Process A interrupted\n");
	exit(0);
}

int main(int argc, char** argv){
	signal(SIGINT, f);
	shmid = shmget(1234, sizeof(struct shared_mem), IPC_CREAT | 0600);
	m = shmat(shmid, 0, 0);
	A2B = open("AtoB", O_WRONLY);
	write(A2B, m, sizeof(struct shared_mem));
	printf("Process A at while!\n");
	while(1){
		scanf("%s", m->string);
	}
	return 0;
}
