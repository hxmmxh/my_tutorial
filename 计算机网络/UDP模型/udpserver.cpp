#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

#define SERV_PORT 7777
#define MAXLINE 1024

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];
    for (;;)
    {
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}

int main(int argc, char **argc)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}