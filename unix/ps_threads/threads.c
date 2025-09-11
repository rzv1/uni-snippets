#include <pthread.h>
#include <unisdt.h>
#include <stdlib.h>

int main(int argc, char** argv){
	pthread_t t[100];
	for(int i = 0; i < 101; i++){
		pthread_create(t[i], 
