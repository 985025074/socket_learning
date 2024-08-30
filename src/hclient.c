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
    while(1){
        printf("operator: \n");
        char operator = getchar();
        if (operator == 'q'){
            char empty_buffer[4] = {0};
            writeWithCheck(sockfd, empty_buffer, 4,"fail to send q to server");
            close(sockfd);
            return 0;
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
        int read_result = read(sockfd, buffer, 4);
        checkTrue(read_result >0, "read() failed");
        printf("%d\n", *((int*)buffer));
        free(pack);
    }

}