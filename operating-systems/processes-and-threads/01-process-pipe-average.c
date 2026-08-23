

/* Create a C program that generates N random integers (N given at the command line). 
 * It then creates a child, sends the numbers via pipe. 
 * The child calculates the average and sends the result back.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
	if(argc != 2){
		perror("Invalid usage!");
		exit(1);
	}
	srand(time(0));
	int n = atoi(argv[1]);
	int k[n], p[2][2], nr;

	pipe(p[0]); pipe(p[1]);
	
	for(int i = 0; i < n; i++) //Generate numbers
		k[i] = rand() % 1000;
	
	if(fork() == 0){ //Child process
		close(p[0][1]); close(p[1][0]);
		
		read(p[0][0], &n, sizeof(int)); //Read the counter
		int suma = 0;
		printf("Read from parent: ");
		for(int i = 0; i < n; i++){
			read(p[0][0], &nr, sizeof(int)); //Read the numbers
			printf("%d ", nr);
			suma += nr;
		}
		int media = suma / n;
		write(p[1][1], &media, sizeof(int));
	}
	else{ //Parent process
		close(p[0][0]); close(p[1][1]);

		write(p[0][1], &n, sizeof(int)); //First, write the counter in the pipe
		for(int i = 0; i < n; i++)
			write(p[0][1], &k[i], sizeof(int));
		
		read(p[1][0], &nr, sizeof(int));
		printf("The average is %d\n", nr);
		wait(0);
	}
	return 0;
}
