#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int randfail(){
	int n = rand();
	if(n % 3 == 1)
		return 1;
	else
		return 0;
}

int blitz(int k){
	if(k % 7 == 0)
		return 1;
	else
		return 0;
}

int main(int argc, char** argv){
	srand(time(0));
	if(argc != 2){
		perror("Invalid usage!\n");
		exit(1);
	}
	int n = atoi(argv[1]), k = 1;
	int p[n][2], ind;
	for(int i = 0; i < n; i++)
		pipe(p[i]);
	for(int i = 0; i < n; i++){
		if(fork() == 0){
			ind = i;
			for(int j = 0; j < n; j++)
				if(i == j)
					close(p[j][0]);
				else if(i+1 == j)
					close(p[j][1]);
				else{
					close(p[j][0]); close(p[j][1]);
				}
		}
		else{
			for(int j = 1; j < n-1; j++){
				close(p[j][0]); close(p[j][1]);
			}
			close(p[0][0]); close(p[n-1][1]);
			write(p[0][1], &k, sizeof(int));
			while(1){
				printf("Proces %d ", getpid());
				read(p[n-1][0], &k, sizeof(int));
				printf("a citit %d\n", k);
				if(blitz(k)){
					printf("Blitz!\n");
					if(randfail() || k == -1){
						k = -1;
						write(p[0][1], &k, sizeof(int));
						wait(0);
						printf("Joc incheiat!\n");
						exit(0);
					}
				}
				k++;
				write(p[0][1], &k, sizeof(int));
			}
		}
	}
	while(1){
		printf("Proces %d ", getpid());
		read(p[ind][0], &k, sizeof(int));
		printf("a citit %d\n", k);
		if(blitz(k)){
			printf("Blitz!\n");
			if(randfail() || k == -1){
				k = -1;
				write(p[0][1], &k, sizeof(int));
				wait(0);
				exit(0);
			}
		}
		k++;
		write(p[0][1], &k, sizeof(int));
	}
	return 0;
}
