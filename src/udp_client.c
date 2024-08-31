#include "normal_include.h"

int main(){
    // just show the usage of UDP server.
    // ignore the safety check.
    sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6666);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int server_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    socklen_t addr_len = sizeof(server_addr);
    bind(server_socket,(struct sockaddr*)&server_addr,addr_len);

    char recv_buf[1024] = "shiyicong!";
    sendto(server_socket,recv_buf,1024,0,(struct sockaddr*)&server_addr,addr_len);
    printf("Send message: %s\n",recv_buf);
    
    close(server_socket);

    return 0;
}