#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 4096
#define SRVPORT 3000

int main(int argc, char const *argv[])
{
    int socketfd, n;
    char sendline[MAXLINE];
    struct sockaddr_in serverAddress;

    if ( argc != 2 )
    {
        printf("Usage: ./tcpClient <IP>\n");
        return 0;
    }

    if ( (socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }
    

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SRVPORT);
    if ( inet_pton(AF_INET, argv[1], &serverAddress.sin_addr) <= 0 )
    {
        printf("inet_pton error for %s\n",argv[1]);
        return 0;
    }
    
    if ( connect(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 )
    {
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    
    printf("send msg to server(%s): \n", argv[1]);
    fgets(sendline, MAXLINE, stdin);

    if ( send(socketfd, sendline, strlen(sendline), 0) < 0 )
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    close(socketfd);

    return 0;
}
