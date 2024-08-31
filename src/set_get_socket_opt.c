
#include "normal_include.h"
//该程序用以测试getsocketopt和setsocketopt函数的使用
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
    uint32_t size;
    uint32_t length;
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,(socklen_t*)&length);
    printf("default_length:%d\n",size);
    size = 6666;
    setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,sizeof(size));  
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,(socklen_t*)&length);
    printf("after set 6666 length:%d\n",size);
    size = 7777;
    setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,sizeof(size));  
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,(socklen_t*)&length);
    printf("after set 7777 length:%d\n",size);
    size = __INT32_MAX__;
    setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,sizeof(size));  
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void*)&size,(socklen_t*)&length);
    printf("after set VERYBIG length:%d\n",size);
    close(sockfd);
    return 0;
}