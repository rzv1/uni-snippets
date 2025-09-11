#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

/* Write a C program that reads a matrix of integers from a file. 
 * It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. 
 * The main process waits for the threads to finish, then prints the sums.
 */

typedef struct{
	int* line_start;
	int count;
} data;

void* fc(void* arg){
	data dt = *((data*) arg);
	int count = dt.count, sum = 0;	
	for(int i = 0; i < count; i++){
		sum += *(dt.line_start + i);
	}
	int *res = malloc(sizeof(int));
	*res = sum;
	free(arg);
	return res;
}

int main(){
	FILE* f = fopen("matrix", "r");
	int n, m, total_sum = 0;
	
	(void)fscanf(f, "%d", &n);
	(void)fscanf(f, "%d", &m);
	int mat[n][m];
	pthread_t t[n];
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(f, "%d", &mat[i][j]);
	
	for(int i = 0; i < n; i++){
		data* d = malloc(sizeof(data));
		d->line_start = mat[i];
		d->count = m;
		pthread_create(&t[i], NULL, fc, (void*) d);
	}
	
	for(int i = 0; i < n; i++){
		void* p;
		pthread_join(t[i], &p);
		total_sum += *((int*) p);
		free(p);
	}
	printf("The sum is %d!\n", total_sum);
	return 0;
}
