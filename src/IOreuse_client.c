
#include "normal_include.h"

int main(int argc, char *argv[]){
    checkArgs(argc,3,"args is not enough\n");
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    checkTrue(sockfd>=0,"create socket failed\n");
   

    checkTrue(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))>=0,"accept failed\n");
    printf("connect succeed!\n");
    char buffer[1024];
    scanf("%s",buffer);
    if(strcmp(buffer,"exit") == 0){
        shutdown(sockfd,SHUT_RDWR);
        return 0;
    }
    writeWithCheck(sockfd, buffer, strlen(buffer), "write failed\n");
    close(sockfd);
    return 0;
}