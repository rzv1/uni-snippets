#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Ca sa functioneze cu n, se fac urmatoarele precizari:
//  1) consideram ca procesele i si (i+1)%n comunica prin pipe i.
//     => vom inchide toate capetele pentru fiecare pipe excluzand
//        doar pentru scriere in procesul i, si pentru citire in
//		  procesul i+1 al pipe-ului i.
//  2) avand in vedere ca trebuie sa dau fork de n ori, este mai
//     eficient sa apelez un subprogram pentru fiecare proces nou
//     pentru a 

int main(int argc, char** argv){
	int n;
	if(argc != 2){
		printf("Invalid input!\n");
		exit(1);
	}
	else
		n = atoi(argv[1]);
	int p[n][2];
	for(int i = 0; i < n; i++)
		pipe(p[i]);
	for(int i = 0; i < n; i++){
		if(fork() == 0){
			int k;
			for(int j = 0; j < n; j++){
				//if(i != j && (i+1)%n != j){
				//	close(p[j][0]);
				//	close(p[j][1]);
				//}
				//else if(i == j)
				//	close(p[i][1]);
				//else if((i+1)%n == j)
				//	close(p[i][0]);
				if (j != i) close(p[j][0]);
				if (j != (i+1)%n) close(p[j][1]);
			}
			while(1){
				read(p[i][0], &k, sizeof(int));
				if(k <= 0)
					break;
				printf("Procesul %d -> %d a primit %d\n", i, i+1, k);
				fflush(stdout);
				k--;
				write(p[(i+1)%n][1], &k, sizeof(int));
			}
			close(p[i][0]);
			close(p[(i+1)%n][1]);
			exit(0);
		}
	}
	for(int j = 1; j < n-1; j++){
		close(p[j][0]);
		close(p[j][1]);
	}
	close(p[0][0]);
	close(p[n-1][1]);
	sleep(1);
	int k = 99;
	write(p[0][1], &k, sizeof(int));
	while(1){
		read(p[n-1][0], &k, sizeof(int));
		if(k <= 0)
			break;
		k--;
		write(p[0][1], &k, sizeof(int));
	}
	for(int i = 0; i < n; i++)
		wait(0);
	close(p[n-1][0]);
	close(p[0][1]);
	return 0;
}
