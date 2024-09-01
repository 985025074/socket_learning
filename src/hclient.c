#include "normal_include.h"
void write_process(int sockfd){
    while(1){
        printf("operator: \n");
        char operator = getchar();
        if (operator == 'q'){
            shutdown(sockfd, SHUT_WR);
            return;
        }
        printf("operator number:\n");
        uint32_t operator_number = 0;
        scanf("%d", &operator_number);
        char * pack = (char*)malloc(sizeof(char)*(operator_number*4+4+1));
        memcpy(pack, (char*)&operator_number,4);

        for(uint32_t i = 0; i<operator_number; i++){
            printf("The %d th number:\n",i);
            scanf("%d", (int*)&pack[4+i*4]);
        }
        getchar();
        pack[4+operator_number*4] = operator;
        int write_result = write(sockfd, pack, sizeof(char)*(operator_number*4+4+1));
        checkTrue(write_result >0, "write() failed");
        free(pack);
        sleep(1);
        

        }
}
void read_process(int sockfd){
    char buffer[1024] = {0};
    while(1){
        int read_result = read(sockfd, buffer, 4);
        if(read_result < 0){
            printf ("read over,with result %d\n", read_result);
            return;
        }
        if (read_result == 0){
            printf("socket closed\n");
            return;
        }
        printf("%d\n", *((int*)buffer));
    }
}
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
    pid_t pid = fork();
    if(pid == 0){
        read_process(sockfd);
    }else{
        write_process(sockfd);
    }
    return 0;
}