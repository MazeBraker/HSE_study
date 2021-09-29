#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char const *argv[]) {
    int stat, K;
    struct addrinfo hints = {
            .ai_family = AF_INET, .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *addrs = NULL;
    signal(SIGPIPE, SIG_IGN);

//    if (sscanf(argv[2], "%d%n", &port, &tmp) != 1 || argv[2][tmp] ||
//        port <= 0 || port > 65535) { // read port
//        fprintf(stderr, "Bad port number: %s\n", argv[2]);
//        exit(0);
//    }
    stat = getaddrinfo(argv[1], argv[2], &hints, &addrs);
    // Полностью дифф ошибки, удобно для дебага
    //getaddrinfo
    if (stat != 0) {
        printf("%s\n", gai_strerror(stat));
        exit(0);
    }

    int sofd1 = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (sofd1 == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(0);
    }

    stat = connect(sofd1, addrs->ai_addr, addrs->ai_addrlen);
    if (stat == -1) {
        fprintf(stderr, "connect error: %s\n", strerror(errno));
        exit(0);
    }

    int sockfd2 = dup(sofd1);
    if (sockfd2 == -1) {
        fprintf(stderr, "dup error: %s\n", strerror(errno));
        exit(0);
    }
    // FILE *socket_file_in = fdopen(client.socket, "r");
    //    FILE *socket_file_out = fdopen(client.socket, "w");

    FILE *fd_host = fdopen(sofd1, "r");
    if (!fd_host) {
        fprintf(stderr, "fdopen error: %s\n", strerror(errno));
        exit(0);
    }

    FILE *fd_server = fdopen(sockfd2, "w");
    if (!fd_server) {
        fprintf(stderr, "fdopen error: %s\n", strerror(errno));
        exit(0);
    }

    stat = fprintf(fd_server, "%s\n", argv[3]);
    fflush(fd_server);
    if (stat < 0) {
        fprintf(stderr, "write error: %s\n", strerror(errno));
        exit(0);
    }

    stat = fscanf(fd_host, "%d", &K);
    if (stat < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        exit(0);
    }

    for (int i = 0; i <= K; ++i) {
        stat = fprintf(fd_server, "%d\n", i);
        fflush(fd_server);
        // wait(10)
        if (stat < 0) {
            fprintf(stderr, "write error: %s\n", strerror(errno));
            exit(0);
        }
    }

    uint64_t num;
    stat = fscanf(fd_host, "%llu", &num);
    if (stat < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        exit(0);
    }

    printf("%llu\n", num);
    fflush(stdout);

    freeaddrinfo(addrs);
    fclose(fd_host);
    fclose(fd_server);
    
    return 0;
}
