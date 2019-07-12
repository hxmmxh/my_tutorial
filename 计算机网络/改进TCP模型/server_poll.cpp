#include <sys/types.h>  //
#include <sys/socket.h> //socket,bind,connect,listen,accept,sockaddr_in,sockaddr
#include <poll.h>       //poll
#include <sys/stropts.h> //INFTIM
#include <arpa/inet.h>  //地址转换函数
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>
#include <algorithm>
#include <limits.h>

#define MAXLINE 4096
#define SERV_PORT 3000
#define LISTENQ 1024
#define INFTIM -1
#define OPEN_MAX 1024

int main()
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    size_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
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
        std::cout << "bind listen socket error."<<std::endl;
        return -1;
    }

    if (listen(listenfd, LISTENQ) == -1)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i < OPEN_MAX; ++i)
        client[i].fd = -1;
    maxi = 0;

    for (;;)
    {
        nready = poll(client, maxi + 1, INFTIM);
        if (client[0].revents & POLLRDNORM)
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            for (i = 1; i < OPEN_MAX; ++i)
                if (client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    break;
                }
            if (i == OPEN_MAX)
            {
                std::cout << "too many clients" << std::endl;
                return -1;
            }
            client[i].events = POLLRDNORM;
            if (i > maxi)
                maxi = i;
            if (--nready <= 0)
                continue;
        }
        for (i = 1; i <= maxi; ++i)
        {
            if ((sockfd = client[i].fd) < 0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR))
            {
                if ((n = read(sockfd, buf, MAXLINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                    {
                        std::cout << "read error" << std::endl;
                        return -1;
                    }
                }
                else if (n == 0)
                {
                    close(sockfd);
                    client[i].fd = -1;
                }
                else
                    write(sockfd, buf, n);
                if (--nready <= 0)
                    break;
            }
        }
    }
}
