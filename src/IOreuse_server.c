#include "normal_include.h"
// IO 复用方式，类似单核运行多个进程的方式
// 基本结构，主循环while(1)内部一个for循环遍历所有的socket(利用socket编码从小到大的特点)
int main(int argc, char *argv[])
{
    checkArgs(argc, 2, "args is not enough");
    printf("Hello, world!\n");
    struct sockaddr_in example;
    memset(&example, 0, sizeof(example));
    example.sin_family = AF_INET;
    example.sin_port = htons(atoi(argv[1]));
    example.sin_addr.s_addr = htons(INADDR_ANY);
    //
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    checkReturn(sockfd > 0, 1, "socket error");
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    //
    int bind_result = bind(sockfd, (struct sockaddr *)&example, sizeof(example));
    checkReturn(bind_result, 0, "bind error");

    int listen_result = listen(sockfd, 5);
    checkReturn(listen_result, 0, "listen error");
    int max_sockfd = sockfd + 1;
    fd_set backup;
    fd_set used;
    FD_ZERO(&backup);
    FD_SET(sockfd, &backup);
    while (1)
    {
        used = backup;
        int select_result = select(max_sockfd, &used, NULL, NULL, NULL);
        if (select_result < 0)
        {
            perror("select error");
        }
        // 开始接受，注意，tcp 中无论是连接还是断开本质都是信息read端的变化
        for (int i = 0; i < max_sockfd; i++)
        {
            if (FD_ISSET(i, &used))
            {
                if (i == sockfd)
                {
                    // 新连接
                    struct sockaddr_in client_addr;
                    socklen_t client_addr_len  = sizeof(client_addr);
                    int accept_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
                    if (accept_socket > 0)
                    {
                        if (accept_socket + 1> max_sockfd)
                        {
                            max_sockfd = accept_socket + 1;
                        }
                        FD_SET(accept_socket, &backup);
                        printf("client ip: %s,client port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    }
                }
                else
                {
                    char buffer[1024];
                    int read_len = read(i, buffer, sizeof(buffer));
                    if (read_len == 0)
                    {
                        printf("disconnect\n");
                        FD_CLR(i, &backup);
                        close(i);
                    }
                    else
                    {
                        printf("%s\n", buffer);
                    }
                }
            };
        }
    }
    return 0;
}
