#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {
    char host[1001];
    char service[1001];

    struct addrinfo hints = {
            .ai_family = AF_INET, .ai_flags = 0, .ai_socktype = SOCK_STREAM
    };

    struct addrinfo *result, *now;
    struct sockaddr_in *ipv4, *min_ipv4 = NULL;
    // имя хоста и сервис
    while (scanf("%s %s", host, service) == 2) {
        int stat = getaddrinfo(host, service, &hints, &result);

        if (stat != 0) {
            //fprintf(stderr, "error: %s\n", gai_strerror(stat));
            printf("%s\n", gai_strerror(stat));
            continue;
        }

        for (now = result; now != NULL; now = now->ai_next) {
            ipv4 = (struct sockaddr_in *) now->ai_addr;

            if (min_ipv4 != NULL) {

                uint32_t cur = ntohl(ipv4->sin_addr.s_addr);
                uint32_t last = ntohl(min_ipv4->sin_addr.s_addr);
                // запоминаем минимальное по условию
                if (cur < last)
                    min_ipv4 = ipv4;
            } else {
                min_ipv4 = ipv4;
            }
        }

        printf("%s:%d\n", inet_ntoa(min_ipv4->sin_addr), ntohs(min_ipv4->sin_port));

        freeaddrinfo(result);
        // не обязательно,
       // *host = '\0';
       // *service = '\0';

        min_ipv4 = NULL;
    }
    return 0;
}