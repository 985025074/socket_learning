
#include "normal_include.h"
//该程序用以验证half-close的tcp
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
    char buffer[10] = {0};
    readWithCheck(sockfd,buffer,10,"read failed\n");
    printf("receive:%s\n",buffer);
    writeWithCheck(sockfd,"Thanks\n",sizeof("Thanks\n"), "write failed\n");
    close(sockfd);
    return 0;
}