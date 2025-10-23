// Un client trimite unui server un sir de caractere si doua numere (fie acestea s, i, l). Serverul va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main() {
	char* s;
	int c;
	uint16_t i, l;
	struct sockaddr_in server;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0) {
		perror("Socket creation\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("Connection to server\n");
		return 1;
	}

	printf("Sir: ");
	scanf("%s", s);
	printf("i: ");
	scanf("%hu", &i);
	printf("l: ");
	scanf("%hu", &l);
	
	uint16_t s_len = strlen(s);
	s_len = htons(s_len);
	send(c, &s_len, sizeof(s_len), 0);
	send(c, s, strlen(s), 0);
	i = htons(i);
	l = htons(l);
	send(c, &i, sizeof(i), 0);
	send(c, &l, sizeof(l), 0);
	recv(c, &s_len, sizeof(s_len), MSG_WAITALL);
	s_len = ntohs(s_len);
	char* sir = malloc(s_len+1);
	sir[s_len] = '\0';
	recv(c, sir, s_len, MSG_WAITALL);
	printf("Am primit %s\n", sir);
	printf("Ma inchid\n");
	close(c);
}
