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
    int listenfd, connectfd;
    struct sockaddr_in serverAddress;
    char buffer[MAXLINE];
    int n;

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(SRVPORT);

    if ( bind(listenfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress) ) == -1 )
    {
        printf("bind socket error: %s(errno: %d)", strerror(errno), errno);
        return 0;
    }

    if ( listen(listenfd, 10) == -1 )
    {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    
    printf(" ======waiting for client's request====== \n");

    while (1)
    {
        if (  (connectfd = accept(listenfd, (struct sockaddr *)NULL, NULL) ) == -1 )
        {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }

        n = recv(connectfd, buffer, MAXLINE,0);

        buffer[n] = '\0';
        printf("recv msg from client: %s\n", buffer);
        close(connectfd);
        
    }
    
    close(listenfd);
    
    return 0;
}
