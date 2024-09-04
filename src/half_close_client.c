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

    connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    //check
    printf("OK\n");
    FILE * fp = fdopen(sockfd,"wr");
    char buffer[1024] = {0};
    while(1){
        if(fread(buffer,1,1024,fp) >0){
            printf("%s",buffer);
            fflush(stdout);
        }
        else{
            break;
        }
    }
    fprintf(fp,"exit\n");
    fclose(fp);
    close(sockfd);
    
    return 0;
}