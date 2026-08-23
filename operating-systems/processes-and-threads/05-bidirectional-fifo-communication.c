#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

/* Write two C programs that communicate via fifo. 
 * The two processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. 
 * Print messages as the numbers are sent. 
 * One of the two processes must be responsible for creating and deleting the fifos.
 */

int main(int argc, char** argv){
	int n=0;
	srand(time(0));
	
	if(0 > mkfifo("AtoB", 0600))
		perror("mkfifo error");
	if(0 > mkfifo("BtoA", 0600))
		perror("mkfifo error");
	
	if(fork() == 0){
		//Child A
	    int a2b = open("AtoB", O_WRONLY);
		int b2a = open("BtoA", O_RDONLY);
		n = rand() % 101;
		write(a2b, &n, sizeof(int));

		while(n != 100){
			read(b2a, &n, sizeof(int));
			printf("Process %d: Read number %d\n", getpid(), n);
		
			if(n == 100)
				break;
			n = rand() % 101;
			write(a2b, &n, sizeof(int));
			printf("Process %d: Write number %d\n", getpid(), n);
		}
		printf("Process %d: Done!\n", getpid());
		close(a2b); close(b2a);
	}
	else if(fork() == 0){
		//Child B
		int a2b = open("AtoB", O_RDONLY);
		int b2a = open("BtoA", O_WRONLY);
		while(n != 100){
			read(a2b, &n, sizeof(int));
			printf("Process %d: Read number %d\n", getpid(), n);	
			if(n == 100)
				break;
			n = rand() % 101;
			write(b2a, &n, sizeof(int));
			printf("Process %d: Write number %d\n", getpid(), n);
		}
		printf("Process %d: Done!\n", getpid());
		close(a2b); close(b2a);
	}
	else{ //Parent process
		wait(0);
		wait(0);
	}
	return 0;
}
