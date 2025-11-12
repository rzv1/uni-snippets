// server_protocol.c
// Compile: gcc -std=c11 -O2 -Wall -o server_protocol server_protocol.c
// Run: ./server_protocol 12345

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BACKLOG 5
#define BUFSIZE 4096

// send_all: trimite tot bufferul
ssize_t send_all(int fd, const void *buf, size_t len) {
    size_t total = 0;
    const char *p = buf;
    while (total < len) {
        ssize_t s = send(fd, p + total, len - total, 0);
        if (s <= 0) return -1;
        total += s;
    }
    return total;
}

// recv_line: citeste pana la '\n', returneaza alocat (trebuie free), fara '\n'
char* recv_line(int fd) {
    char tmp[BUFSIZE];
    size_t pos = 0;
    while (1) {
        ssize_t r = recv(fd, tmp + pos, 1, 0);
        if (r <= 0) return NULL;
        if (tmp[pos] == '\n') {
            tmp[pos] = '\0';
            char *res = strdup(tmp);
            return res;
        }
        pos++;
        if (pos >= BUFSIZE - 1) return NULL;
    }
}

// util: uppercase a string in place
void to_upper_inplace(char *s) {
    for (; *s; ++s) *s = (char) toupper((unsigned char)*s);
}

// util: split string by spaces into tokens (returns array of pointers, count via out_count)
// tokens are pointers inside the copy string
char** split_words(char *s, int *out_count) {
    int cap = 8, cnt = 0;
    char **arr = malloc(cap * sizeof(char*));
    char *p = strtok(s, " \t\r\n");
    while (p) {
        if (cnt >= cap) { cap *= 2; arr = realloc(arr, cap * sizeof(char*)); }
        arr[cnt++] = p;
        p = strtok(NULL, " \t\r\n");
    }
    *out_count = cnt;
    return arr;
}

int handle_client(int client_fd) {
    char sendbuf[BUFSIZE];
    char *line = NULL;

    // 1. WELCOME
    snprintf(sendbuf, sizeof(sendbuf), "WELCOME\n");
    if (send_all(client_fd, sendbuf, strlen(sendbuf)) < 0) return -1;

    // 2. TASK1 ask for N
    snprintf(sendbuf, sizeof(sendbuf), "TASK1: SEND_N\n");
    if (send_all(client_fd, sendbuf, strlen(sendbuf)) < 0) return -1;

    // 3. recv N
    line = recv_line(client_fd);
    if (!line) return -1;
    long N = strtol(line, NULL, 10);
    free(line);
    if (N <= 0 || N > 10000) {
        snprintf(sendbuf, sizeof(sendbuf), "ERROR: invalid N\n");
        send_all(client_fd, sendbuf, strlen(sendbuf));
        return -1;
    }

    // 4. ask for N lines Name Age
    snprintf(sendbuf, sizeof(sendbuf), "SEND_PEOPLE\nFormat: <Name> <Age> (one per line)\n");
    if (send_all(client_fd, sendbuf, strlen(sendbuf)) < 0) return -1;

    long sum_age = 0;
    for (long i = 0; i < N; ++i) {
        line = recv_line(client_fd);
        if (!line) return -1;
        // parse: name (no spaces) + age
        char name_buf[256];
        long age;
        int matched = sscanf(line, "%255s %ld", name_buf, &age);
        free(line);
        if (matched != 2 || age < 0 || age > 200) {
            snprintf(sendbuf, sizeof(sendbuf), "ERROR: invalid input on line %ld\n", i+1);
            send_all(client_fd, sendbuf, strlen(sendbuf));
            return -1;
        }
        sum_age += age;
    }

    double avg = (double)sum_age / (double)N;
    snprintf(sendbuf, sizeof(sendbuf), "ANSWER1: %.2f\n", avg);
    if (send_all(client_fd, sendbuf, strlen(sendbuf)) < 0) return -1;

    // 6. TASK2: request a string
    snprintf(sendbuf, sizeof(sendbuf), "TASK2: SEND_STRING\nDescribe: server will uppercase and reverse word order\n");
    if (send_all(client_fd, sendbuf, strlen(sendbuf)) < 0) return -1;

    // 7. receive the string line
    line = recv_line(client_fd);
    if (!line) return -1;

    // process: uppercase + reverse word order
    // make a modifiable copy
    char *copy = strdup(line);
    free(line);
    to_upper_inplace(copy);
    int cnt = 0;
    char **words = split_words(copy, &cnt);
    // build reversed output
    size_t outcap = 1024, outlen = 0;
    char *out = malloc(outcap);
    out[0] = '\0';
    for (int i = cnt - 1; i >= 0; --i) {
        size_t need = strlen(words[i]) + 2;
        if (outlen + need >= outcap) {
            outcap = (outlen + need) * 2;
            out = realloc(out, outcap);
        }
        if (outlen) { out[outlen++] = ' '; out[outlen] = '\0'; }
        strcat(out, words[i]);
        outlen = strlen(out);
    }
    if (cnt == 0) {
        strcpy(out, "");
    }

    // send ANSWER2
    snprintf(sendbuf, sizeof(sendbuf), "ANSWER2: %s\n", out);
    send_all(client_fd, sendbuf, strlen(sendbuf));

    // cleanup
    free(copy);
    free(words);
    free(out);

    // final
    snprintf(sendbuf, sizeof(sendbuf), "DONE\n");
    send_all(client_fd, sendbuf, strlen(sendbuf));
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    if (port <= 0) { fprintf(stderr, "Invalid port\n"); return 1; }

    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(srv, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); close(srv); return 1; }
    if (listen(srv, BACKLOG) < 0) { perror("listen"); close(srv); return 1; }

    printf("Server listening on 0.0.0.0:%d\n", port);
    while (1) {
        struct sockaddr_in cli;
        socklen_t clen = sizeof(cli);
        int cli_fd = accept(srv, (struct sockaddr*)&cli, &clen);
        if (cli_fd < 0) { perror("accept"); continue; }
        printf("Client from %s:%d connected\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        if (handle_client(cli_fd) < 0) {
            printf("Client handling error or disconnect\n");
        } else {
            printf("Client finished successfully\n");
        }
        close(cli_fd);
    }
    close(srv);
    return 0;
}
