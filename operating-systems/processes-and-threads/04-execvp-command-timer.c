#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
	time_t sec_start, sec_finish;
	sec_start = time(0);
	if(argc < 2){
		perror("Invalid usage!\n");
		exit(1);
	}
	if(fork() == 0){
		execvp(argv[1], &argv[1]);
		perror("Command error!\n");
	}
	wait(0);
	sec_finish = time(0);
	printf("Command executed in %ld seconds\n", sec_finish - sec_start);
	return 0;
}
