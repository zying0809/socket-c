#include<stdio.h>
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
    if ( argc != 2 )
    {
        printf("Usage: ./upd-client <IP>\n");
        return 0;
    }

    int sockfd;
    struct sockaddr_in srvAddr; 
    char sendline[MAXLINE];

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SRVPORT);
    if ( inet_pton(AF_INET, argv[1], &srvAddr.sin_addr) <= 0 )
    {
        printf("inet_pton error for %s\n",argv[1]);
        return 0;
    }

    printf("send msg to server(%s): \n", argv[1]);
    fgets(sendline, MAXLINE, stdin);

    if( sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0 )
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    close(sockfd);

    return 0;
}
