#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	struct sockaddr_in s;
	int c;

	// Al treilea argument (protocolul) se specifica doar daca domeniul(primul argument) accepta mai multe tiprui
	// de protocoale.
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0)
		perror("socket creation");
	
	s.sin_port = htons(1234);
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr*) &s, sizeof s) < 0)
		perror("Connection error");

	char cerinta[256];
	recv(c, &cerinta, sizeof cerinta - 1, 0);
	int bytes;
	bytes = recv(c, &cerinta, sizeof cerinta - 1, 0);
	cerinta[bytes] = '\0';
	printf("%s", cerinta);
	uint16_t n = 20, net_n;
	net_n = htons(n);
	send(c, "3\n", 2, 0);
	bytes = recv(c, &cerinta, sizeof cerinta - 1, 0);
	cerinta[bytes] = '\0';
	printf("%s", cerinta);
	send(c, "Ana 10\n", 7, 0);
	send(c, "Boss 14\n", 8, 0);
	send(c, "Mara 7\n", 7, 0);
	bytes = recv(c, &cerinta, sizeof cerinta - 1, 0);
	cerinta[bytes] = '\0';
	printf("%s", cerinta);
	bytes = recv(c, &cerinta, sizeof cerinta - 1, 0);
	cerinta[bytes] = '\0';
	printf("%s", cerinta);
	char string[] = "acestaeuns\n";
	send(c, string, strlen(string)+1, 0);
	bytes = recv(c, &cerinta, sizeof cerinta - 1, 0);
	cerinta[bytes] = '\0';
	printf("%s", cerinta);
	close(c);
}
