#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(){
	struct sockaddr_in s;
	int c;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0)
		perror("socket error");
	
	memset(&s, 0, sizeof s);
	s.sin_port = htons(1234);
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &s, sizeof s) < 0)
		perror("connection error");

	char buf[256];
	int bytes;
	int len = 0;
	recv(c, &buf, sizeof buf, 0);
	recv(c, &buf, sizeof buf, 0);
	while((bytes = recv(c, &buf, sizeof buf - 1, 0)) > 0){
		buf[bytes] = '\0';
		if (strstr(buf, "END\n") != NULL){
			printf("\n");
			break;
			}
	}
	printf("%hu\n", len);
	send(c, "121\n", 4, 0);
	bytes = recv(c, &buf, sizeof buf - 1, 0);
	buf[bytes] = '\0';
	printf("%s", buf);
	bytes = recv(c, &buf, sizeof buf - 1, 0);
	buf[bytes] = '\0';
	printf("%s", buf);
}
