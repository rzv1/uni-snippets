#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/* Write a C program that creates two child processes. 
 * The two child processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. 
 * Print messages as the numbers are sent.
*/

// Unidirectiol communication between Child A & Child B:
// AtoB, BtoA - pipes

int main(int argc, char** argv){
	int AtoB[2], BtoA[2], n=0;
	srand(time(0));
	pipe(AtoB); pipe(BtoA);
	
	if(fork() == 0){
		//Child A
		close(AtoB[0]); close(BtoA[1]);
		n = rand() % 11;
		
		write(AtoB[1], &n, sizeof(int));
		
		while(n != 10){
		read(BtoA[0], &n, sizeof(int));
		printf("Process %d: Read number %d\n", getpid(), n);
		if(n == 10)
			break;

		n = rand() % 11;
		write(AtoB[1], &n, sizeof(int));
		printf("Process %d: Write number %d\n", getpid(), n);
		}
		printf("Process %d: Done!\n", getpid());
	}
	else if(fork() == 0){
		//Child B
		close(AtoB[1]); close(BtoA[0]);
		
		while(n != 10){
			read(AtoB[0], &n, sizeof(int));
			printf("Process %d: Read number %d\n", getpid(), n);	
			
			if(n == 10)
				break;
			n = rand() % 11;
			write(BtoA[1], &n, sizeof(int));
			printf("Process %d: Write number %d\n", getpid(), n);
		}
		printf("Proces %d: Done!\n", getpid());
	}
	else{ //Parent process
		wait(0);
		wait(0);
	}
	return 0;
}
