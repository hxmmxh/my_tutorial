#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

void dg_cli(FILE *fp, int sockfd, const struct sockaddr* pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while(fgets(sendline,MAXLINE,fp)!=NULL)
    {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}



int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2)
    {
        std::cout << "usage: udp: udpcli<IPaddress>" << endl;
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET:
    servaddr.sin_port=htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1],&servaddr.sin_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}