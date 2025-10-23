#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv){
        int c;
        struct sockaddr_in server;
		uint16_t p = (uint16_t) strtoul(argv[2], NULL, 10);

        c = socket(AF_INET, SOCK_STREAM, 0);
        if(c < 0){
                perror("socket creation");
                return 1;
        }
		if(argc != 3){
			printf("Incorrect usage");
			return 1;
		}

        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(p);
        server.sin_addr.s_addr = inet_addr(argv[1]);

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
                perror("connection error");
                return 1;
        }

        uint16_t n, m, k;
        printf("Lungime sir 1: ");
        scanf("%hu", &n);
        uint16_t sir1[n];
        printf("\nElemente sir 1: ");
        for(int i = 0; i < n; i++)
                scanf("%hu", &sir1[i]);
        printf("\nLungime sir 2: ");
        scanf("%hu", &m);
        uint16_t sir2[m];
        printf("\nElemente sir 2: ");
        for(int i = 0; i < m; i++)
                scanf("%hu", &sir2[i]);
        uint16_t net_n = htons(n), net_m = htons(m);
        send(c, &net_n, sizeof(net_n), 0);
        send(c, sir1, sizeof sir1, 0);
        send(c, &net_m, sizeof(net_m), 0);
        send(c, sir2, sizeof sir2, 0);

        recv(c, &k, sizeof(k), MSG_WAITALL);
        uint16_t sir_nou[k];
        k = ntohs(k);
        recv(c, sir_nou, sizeof sir_nou, MSG_WAITALL);

        printf("Rezultat: ");
        for(int i = 0; i < k; i++)
                printf("%hu ", sir_nou[i]);
        close(c);
}
