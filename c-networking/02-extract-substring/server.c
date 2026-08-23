#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int c, s, len;
	uint16_t i,l;
	struct sockaddr_in client, server;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0) {
		perror("Socket creation\n");
		return 1;
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		perror("Socket bind");
		return 1;
	}
	listen(c, 5);
	len = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		uint16_t s_len;
		s = accept(c, (struct sockaddr *) &client, &len);
		printf("S-a conectat!\n");
		recv(s, &s_len, sizeof(s_len), MSG_WAITALL);
		s_len = ntohs(s_len);
		printf("Am primit %hu\n", s_len);
		char* sir = malloc(s_len+1);
		sir[s_len] = '\0';
		recv(s, sir, s_len, MSG_WAITALL);
		recv(s, &i, sizeof(i), MSG_WAITALL);
		recv(s, &l, sizeof(l), MSG_WAITALL);
		i = ntohs(i);
		l = ntohs(l);
		if (strlen(sir) - i < l)
			s_len = strlen(sir) - i;
		else
			s_len = l;
		s_len = htons(s_len);
		send(s, &s_len, sizeof(s_len), 0);
		send(s, sir + i, ntohs(s_len), 0);
		printf("Am trimis %s cu lungime %hu\n", sir + i, ntohs(s_len));
		close(s);
	}
	close(c);
}
