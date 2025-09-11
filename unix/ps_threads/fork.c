#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if(argc != 2){
		perror("Invalid usage!");
		exit(1);
	}
	int N = atoi(argv[1]);
	for(int i = 0; i < N; i++){
		if(fork() == 0){
			printf("Process %d have parent %d\n", getpid(), getppid());
			exit(0);
		}
		else
			wait(0);
	}
	return 0;
}
