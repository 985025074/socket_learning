#include "normal_include.h"
//该程序用以验证half-close的tcp
int main(int argc, char *argv[]){
    checkArgs(argc,2,"args is not enough\n");
    printf("start file server\n");
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    fflush(stdin);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    checkTrue(sockfd>=0,"create socket failed\n");
    checkTrue(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr))>=0,"bind failed\n");
    checkTrue(listen(sockfd, 5)>=0,"listen failed\n");
    struct sockaddr ___addr;
    socklen_t ___len;

    int clientfd = accept(sockfd, &___addr, &___len);
    checkTrue(clientfd>=0,"accept failed\n");
    printf("accept succeed!\n");
    writeWithCheck(clientfd,"hello,world!\n",sizeof("hello,world!\n"), "write failed\n");
    checkTrue(shutdown(clientfd, SHUT_WR)>=0,"shutdown failed\n");
    
    char buffer[10] = {0};
    readWithCheck(clientfd,buffer,10,"read failed\n");
    printf("client say:%s\n",buffer);
    close(clientfd);
    return 0;
}