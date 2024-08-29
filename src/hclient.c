#include "normal_include.h"
int main(int , char* argv[]){



    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    checkTrue(sockfd>0, "socket() failed");
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    int connect_result = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    checkTrue(connect_result == 0, "connect() failed");
    
    printf("connected to %s\n",inet_ntoa(server_addr.sin_addr));
    char buffer[1024] = {0};
    while(scanf("%s", buffer)&&strcmp(buffer,"exit")!=0){
        int write_result = write(sockfd, buffer, strlen(buffer));
        checkTrue(write_result >0, "write() failed");

        int read_result = read(sockfd, buffer, sizeof(buffer));
        checkTrue(read_result >0, "read() failed");

        printf("%s\n", buffer);
    }

}