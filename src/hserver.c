#include "normal_include.h"
int main(int argc, char *argv[]){
    checkArgs(argc,2,"args is not enough");

printf("Hello, world!\n");
   struct sockaddr_in example;
   memset(&example, 0, sizeof(example));
   example.sin_family = AF_INET;
   example.sin_port = htons(atoi(argv[1]));
   example.sin_addr.s_addr = htons(INADDR_ANY);

   int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   checkReturn(sockfd>0,1,"socket error");

   int bind_result = bind(sockfd, (struct sockaddr*)&example, sizeof(example));
   checkReturn(bind_result,0,"bind error");

   int listen_result = listen(sockfd, 5);
   checkReturn(listen_result,0,"listen error");

   for(int i=0;i<5;i++){
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    int accept_socket = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    checkReturn(accept_socket>0,1,"accept error");
    printf("client ip: %s,client port %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    char buffer[1024];
    int read_result;
    while((read_result = read(accept_socket, buffer, 1024))){
        checkTrue(read_result>=0,"read error");
        int write_result = write(accept_socket, buffer, read_result);
        checkTrue(write_result>=0,"write error");
        printf("client send: %s\n",buffer);
        if(strcmp(buffer,"exit") == 0){
            break;
        }
    }
    close(accept_socket);
   }
   return 0;
}