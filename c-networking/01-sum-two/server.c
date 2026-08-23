#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l, a, b, suma;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0){
		printf("Eroare creare socket\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Functia bind conecteaza adresa la socket si e specifica serverului.
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare bind\n");
		return 1;
	}

	// Dupa bind, server-ul asculta pe adresa socketului.
	// int listen(int socket, int backlog);
	// backlog = lungime maxima queue of pending connections.
	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1){ 
		uint16_t a, b, suma;
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a realizat conexiunea\n");

		// Flag-ul MSG_WAITALL - wait for full request or error
		recv(c, &a, sizeof(a), MSG_WAITALL);
		recv(c, &b, sizeof(b), MSG_WAITALL);
		a = ntohs(a);
		b = ntohs(b);
		suma = a + b;
		suma = htons(suma);
		send(c, &suma, sizeof(suma), 0);
		close(c);
	}
	close(s);
}
