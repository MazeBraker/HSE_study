#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <time.h>
#include <netinet/in.h>
// основа взята с семинара 199
int main(int argc, char**argv) {
     struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(atoi(argv[1])),
            .sin_addr.s_addr = INADDR_ANY
    };

    
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    if (lfd  < 0) {
        //fprintf(stderr, "%s\n", "error in socket creating");
        _exit(0);
    }
    int val = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));


    if(bind(lfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        //fprintf(stderr, "%s\n", "error in bind");
        close(lfd);
        _exit(0);
    }

    if(listen(lfd, 5) < 0) {
        //fprintf(stderr, "%s\n", "error in listen");
        close(lfd);
        _exit(0);
    } 
    int32_t res = 0, scan = 1;
    // если scan 0, то это последний клиент и все!
    while(scan) {
        int size = sizeof(addr);
        int sfd = accept(lfd, (struct sockaddr *) &addr, (socklen_t *) &size);

        if (sfd < 0){
           _exit(0);
        }

        read(sfd, &scan, sizeof(scan));

        close(sfd);

        scan = ntohl(scan);
        res += scan;
        
    }
    printf("%d\n", res);
    fflush(stdout);
    //freeaddrinfo(addr);
    //close(afd);
    close(lfd);
    return 0;
}