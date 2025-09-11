#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <string.h>

/* Create two processes A and B. 
 * A creates a shared memory segment. 
 * A then keeps reading strings from the standard input and places whatever it reads in the shared memory segment (replacing previous data). 
 * Process B, on each run, reads the data from the shared memory segment and counts the number of vowels. 
 * Process A, upon receiving a SIGINT, deletes the shared memory segment.
 */

struct shared_mem {
	char string[256];
};

int main(int argc, char** argv){
	struct shared_mem *m;
	int A2B = open("AtoB", O_RDONLY);
	read(A2B, m, sizeof(struct shared_mem));
	while(1){
		if(m->string[0] != 0){
			int n = 0;
			for(int i = 0; m->string[i]; i++)
				if(strchr("aeiouAEIOU", m->string[i]) != NULL)
					n++;
			printf("Found %d vowels\n", n);
		}
		else if(m->string[0] == 24){
			break;
		}
	}
	close(A2B);
	printf("Process B done!\n");
	return 0;
}
