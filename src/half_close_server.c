#include "normal_include.h"

int main(int argc, char *argv[]){
    checkArgs(argc,3,"not enogh");

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //check

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    //another check

    listen(sockfd, 10);
    //check

    int clientfd = accept(sockfd, NULL, NULL);
    //check
    printf("OK\n");
    FILE *clientfp_w = fdopen(clientfd, "w");
    FILE *clientfp_r = fdopen(dup(clientfd), "r");
    fprintf(clientfp_w, "Hello, client!\n");
    fprintf(clientfp_w, "I am close!\n");
    fflush(clientfp_w);
    fclose(clientfp_w);
    char buffer[1024] = {0};
    int number =fread(buffer, sizeof(char), 1024,clientfp_r);
    fflush(clientfp_r);
    printf("Client says: %s", buffer);
    printf("number of bytes read: %d\n", number);
    fclose(clientfp_r);
    return 0;
}