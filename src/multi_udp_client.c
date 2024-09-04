#include "normal_include.h"
int main(int, char *argv[]){
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    checkTrue(sockfd > 0,"create socket fail!");

    // 服务器不用设置set multi-udp opt
    struct ip_mreq multi_udp_val;
    multi_udp_val.imr_multiaddr.s_addr = inet_addr(argv[1]); //参数1是多播组地址
    multi_udp_val.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&multi_udp_val,sizeof(multi_udp_val));
    // 服务器设置TTL
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2])); //参数2 是本接受者端口
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)); 

      
    char buf[1024];
    while(recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL) > 0){
        printf("%s\n",buf);
    }
    close(sockfd);
    return 0;
}