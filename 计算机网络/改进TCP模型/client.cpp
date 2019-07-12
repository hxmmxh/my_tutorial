#include <sys/types.h> 
#include <sys/socket.h>//socket,bind,connect,listen,accept,sockaddr_in,sockaddr
#include <sys/select.h>//select
#include <sys/time.h>
#include <arpa/inet.h>//地址转换函数
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>
#include <algorithm>

#define MAXLINE 4096
#define SERV_PORT 3000


void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for (;;)
    {
        if(stdineof==0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = std::max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);
        //套接字可读
        if(FD_ISSET(sockfd,&rset))
        {
            if((n=read(sockfd,buf,MAXLINE))==0)
            {
                if(stdineof==1)
                    return ;
                else
                {
                    std::cout << "str_cli: server terminated prematurely"<<std::endl;
                    return;
                }
            }
            write(fileno(stdout), buf, n);
        }
        //输入可读
        if(FD_ISSET(fileno(fp),&rset))
        {
            if((n=read(fileno(fp),buf,MAXLINE))==0)
            {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            write(sockfd, buf, n);
        }
    }
}

int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc !=2)
    {
        std::cout << "usage: client<IPaddress>" << std::endl;
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
}