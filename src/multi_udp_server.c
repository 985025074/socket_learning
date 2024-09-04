#include "normal_include.h"
int main(int, char *argv[]){
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    checkTrue(sockfd > 0,"create socket fail!");

    // 服务器不用设置set multi-udp opt
    // struct ip_mreq multi_udp_val;
    // multi_udp_val.imr_multiaddr.s_addr = inet_addr(argv[1]);
    // multi_udp_val.imr_interface.s_addr = htonl(INADDR_ANY);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    
    int filefd = open("./hserver.c",O_RDONLY);
    checkTrue(filefd > 0,"open file fail!");
    char buf[1024];
    while(read(filefd,buf,sizeof(buf)) > 0){
        sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr,sizeof(addr));
    }
    close(filefd);
    close(sockfd);
    return 0;
}