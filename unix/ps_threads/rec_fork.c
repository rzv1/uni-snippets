#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/* Write a C program that creates a linear hierarchy of n processes
 * Recursive algorithm
 */

void rec(int n){
	if(n){
		if(fork())
			wait(0);
		else {
		printf("Process %d with parent %d\n", getpid(), getppid());
		rec(n-1);
		}
	}
}

int main(int argc, char** argv){
	if(argc != 2){
		perror("Invalid usage!");
		exit(1);
	}
	int n = atoi(argv[1]);
	rec(n);
	return 0;
}
