#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int parent, child;

void f(int sig){
	if(getpid() == parent){
		kill(child, sig);
		printf("Trimit semnal la copil!\n");
		exit(0);
	}
	else if(getpid() == child){
		printf("Am primit semnal si ma opresc!\n");
		exit(0);
	}
	else
		perror("Eroare!");
}

int main(int argc, char** argv){
	signal(SIGUSR1, f);
	if(fork()){
		parent = getpid();
		wait(0);
	}
	else{
		child = getpid();
		while(1){}
	}
	return 0;
}
