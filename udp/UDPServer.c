#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 4096
#define SRVPORT 5000

int main(int argc, char const *argv[])
{
    printf("Welcome! This is a UDP server\n");
    
    int sockfd, len, n;
    struct sockaddr_in srvAddr, cliAddr;
    char buffer[MAXLINE];

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        printf("Create socket failure: %s (errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    
    memset(&srvAddr, 0, sizeof(srvAddr));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SRVPORT);
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( bind(sockfd, (struct sockaddr *)&srvAddr, sizeof(srvAddr) ) == -1 )
    {
        printf("bind socket error: %s(errno: %d)", strerror(errno), errno);
        return 0;
    }
    printf("Started UDP Server Success.\n");
    while (1)
    {
        // recv data
        memset(&cliAddr, 0, sizeof(cliAddr)); 
        if ( (n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliAddr, &len)) < 0 ) {
            printf("recvfrom error: %s(errno: %d)", strerror(errno), errno);
            continue;
        }
        buffer[n] = 0;
        printf("recv: %s\n", buffer); 
    }
    
    close(sockfd);

    return 0;
}
