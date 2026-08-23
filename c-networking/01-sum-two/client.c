#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
struct sockaddr_in {
	short sin_family; // AF_INET
	unsigned short sin_port; // portul
	struct in_addr sin_addr; // adresa IP
	char sin_zero[8];
};
*/

int main(){ 
	int c; // socket client-side
	struct sockaddr_in server; // Initiere socket address
	uint16_t a, b, suma;

	// socket(int domain, int type, int protocol);
	// Alegem AF_INET pentru IPv4 si AF_INET6 pentru IPv6
	// La type: SOCK_STREAM pentru TCP, SOCK_DGRAM pentru UDP si SOCK_RAW pentru IP direct.
	// protocolul este dat de domain, asa ca lasam null
	c = socket(AF_INET, SOCK_STREAM, 0);
	
	// Eroarea returneaza -1
	if (c < 0) {
		printf("Eroare creare socket\n");
		return 1;
	}

	// Initializare socket address
	memset(&server, 0, sizeof(server));

	// Pentru comunicare in retea se foloseste big-endian, astfel ca numerele necesita conversie.
	// little-endian to big-endian: htons (host to network Short(s) sau Long(l))
	// ntohs (network to host short)
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	// Conectam socket-ul la serverul creat anterior
	// connect(int socket, const struct sockaddr *address, socklen_t address_len);
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare conectare la server\n");
		return 1;
	}

	// Acum putem comunica folosind send si recv.
	// send(int socket, const void* buffer, size_t length, int flags);
	// recv(int socket, const void* buffer, size_t length, int flags);
	
	// Cerinta: Sa se trimita 2 numere la server si sa se afiseza suma primita.

	printf("a = ");
	scanf("%hu", &a);
	printf("b = ");
	scanf("%hu", &b);
	a = htons(a);
	b = htons(b);
	send(c, &a, sizeof(a), 0);
	send(c, &b, sizeof(b), 0);
	recv(c, &suma, sizeof(suma), 0);
	suma = ntohs(suma);
	printf("Suma este %hu\n", suma);
	// La final e bine sa se inchida socket-ul
	close(c);
}
