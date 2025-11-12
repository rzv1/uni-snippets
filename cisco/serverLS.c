// server_fragments.c
// Compile: gcc -std=c11 -O2 -Wall -o server_fragments server_fragments.c
// Run: ./server_fragments 1234

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

void send_all(int fd, const char *data) {
    size_t len = strlen(data);
    while (len > 0) {
        ssize_t n = send(fd, data, len, 0);
        if (n <= 0) return;
        data += n;
        len -= n;
    }
}

int recv_line(int fd, char *buf, size_t max) {
    size_t pos = 0;
    while (pos < max - 1) {
        ssize_t n = recv(fd, buf + pos, 1, 0);
        if (n <= 0) return -1;
        if (buf[pos] == '\n') break;
        pos++;
    }
    buf[pos] = '\0';
    return (int)pos;
}

void to_upper(char *s) {
    for (; *s; ++s) *s = toupper((unsigned char)*s);
}

int handle_client(int cfd) {
    char buf[BUFSIZE];
    send_all(cfd, "TASK1: RECEIVE_CHUNKS\n");
    send_all(cfd, "Server will now send a long text in chunks. Collect until you get 'END'\n");

    // Trimite textul în fragmente, cu pauze scurte
    const char *chunks[] = {
        "The quick brown fox ",
        "jumps over the lazy ",
        "dog. END\n"
    };
    for (int i = 0; i < 3; ++i) {
        send_all(cfd, chunks[i]);
        usleep(150000); // 150 ms delay
    }

    // Așteaptă răspuns: lungimea totală
    int n = recv_line(cfd, buf, sizeof(buf));
    if (n <= 0) return -1;
    int len_from_client = atoi(buf);
    int actual_len = strlen("The quick brown fox jumps over the lazy dog. ");
    if (len_from_client != actual_len) {
        send_all(cfd, "WRONG_LENGTH\n");
        close(cfd);
        return 0;
    }

    send_all(cfd, "CORRECT. TASK2: UPPERCASE_TEXT\n");
    send_all(cfd, "Server will send another string in pieces.\n");

    const char *frag2[] = {
        "network programming ",
        "in C is ",
        "fun!\nEND\n"
    };
    for (int i = 0; i < 3; ++i) {
        send_all(cfd, frag2[i]);
        usleep(120000);
    }

    // primește textul complet transformal în majuscule
    n = recv_line(cfd, buf, sizeof(buf));
    if (n <= 0) return -1;

    char expected[256] = "NETWORK PROGRAMMING IN C IS FUN!";
    if (strncmp(buf, expected, strlen(expected)) == 0)
        send_all(cfd, "ANSWER2: OK\nDONE\n");
    else
        send_all(cfd, "ANSWER2: INCORRECT\n");

    close(cfd);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "Usage: %s <port>\n", argv[0]); return 1; }
    int port = atoi(argv[1]);
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(srv, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); exit(1); }
    listen(srv, 5);
    printf("Server listening on port %d\n", port);

    while (1) {
        struct sockaddr_in cli;
        socklen_t clen = sizeof(cli);
        int cfd = accept(srv, (struct sockaddr*)&cli, &clen);
        if (cfd < 0) continue;
        printf("Client connected from %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        handle_client(cfd);
    }
}
