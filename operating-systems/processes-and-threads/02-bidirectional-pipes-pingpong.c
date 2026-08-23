#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
	int n, a2b[2], b2a[2];
	srand(time(0));
	pipe(a2b); pipe(b2a);
	if(fork() != 0){
		close(a2b[0]); close(b2a[1]);
		n = 50 + rand() % 151;
		write(a2b[1], &n, sizeof(int));
		while(1){
		read(b2a[0], &n, sizeof(int));
		printf("Procesul A a citit %d\n", n);
		if(n % 2 == 1)
			n++;
		write(a2b[1], &n, sizeof(int));
		if(n < 5){
			wait(0);
			break;
		}
		}
		printf("Procesul A se incheie\n");
	}
	else{
		close(b2a[0]); close(a2b[1]);
		while(1){
			read(a2b[0], &n, sizeof(int));
			printf("Procesul B a citit %d\n", n);
			n /= 2;
			write(b2a[1], &n, sizeof(int));
			if(n < 5)
				break;
		}
		printf("Procesul B se incheie\n");
	}
	return 0;
}
