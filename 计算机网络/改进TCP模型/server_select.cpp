#include <sys/types.h>  //
#include <sys/socket.h> //socket,bind,connect,listen,accept,sockaddr_in,sockaddr
#include <sys/select.h> //select
#include <sys/time.h>
#include <arpa/inet.h> //地址转换函数
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>
#include <algorithm>

#define MAXLINE 4096
#define SERV_PORT 3000
#define LISTENQ 1024

int main(int argc, char **argv)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    size_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
    {
        std::cout << "bind listen socket error.";
        return -1;
    }

    if (listen(listenfd, LISTENQ) == -1)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    maxfd = listenfd;
    maxi = -1;
    for (i = 0; i < FD_SETSIZE; ++i)
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        //监听描述符变得可读，代表有新的客户接入,因此调用accept获取新的已连接描述符
        if (FD_ISSET(listenfd, &rset))
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            for (i = 0; i < FD_SETSIZE; ++i)
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            if (i == FD_SETSIZE)
            {
                std::cout << "too many clients" << std::endl;
                return -1;
            }
            //把新加入的已连接描述符加到select的描述符集中
            FD_SET(connfd, &allset);
            //修改slect函数的第一个参数
            if (connfd > maxfd)
                maxfd = connfd;
            //client数组中的最大序号
            if (i > maxi)
                maxi = i;
            //没有已就绪的描述符
            if (--nready <= 0)
                continue;
        }
        for (i = 0; i <= maxi; ++i)
        {
            if ((sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset))
            {
                if ((n = read(sockfd, buf, MAXLINE)) == 0)
                {
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    write(sockfd, buf, n);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
}