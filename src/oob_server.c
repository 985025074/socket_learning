#include "normal_include.h"

// IO 复用方式，类似单核运行多个进程的方式
// 基本结构，主循环while(1)内部一个for循环遍历所有的socket(利用socket编码从小到大的特点)
int accept_socket;
void handler(int){
    sysconf(SC_OPEN_MAX);
    char buffer[1024];
    int stle =recv(accept_socket, buffer, sizeof(buffer), MSG_OOB);
    buffer[stle] = 0;
    printf("receive OOB data: %s\n", buffer);
}
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

    accept_socket = accept(sockfd, NULL, NULL);
    printf("connect!\n");
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGURG, &sa, NULL);
    fcntl(accept_socket, F_SETOWN, getpid());
    char buffer[1024];
    sleep(1);
    sleep(1);
    sleep(1);
    sleep(1);
    while(1){
       int strle =read(accept_socket, buffer, sizeof(buffer));
       if(strle == -1){
        printf("error\n");
        perror("recv");
        continue;
       }
       else if(strle == 0){
        break;
       }
        buffer[strle] = 0;

    printf("normal read: %s\n", buffer);
    }
    return 0;
}
