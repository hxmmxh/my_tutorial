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
                    cout << "str_cli: server terminated prematurely";
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