#include "normal_include.h"
#include <errno.h>
#include <stdlib.h>
void child_handler(int){
    //it is said that printf is not safe in signal handler.but i have forgotten the detail,so let us use it temporarily.
    int status = 0;
    int child_pid = waitpid(-1,&status,WNOHANG);
    printf("child process %d terminated\n",child_pid);
    // error handle is dismiss.
    if(WIFEXITED(status)){
        printf("SafeExit!\n");
    }
}
int main(int argc, char *argv[]){
    checkArgs(argc,2,"args is not enough");
    printf("Hello, world!\n");
    struct sigaction sa;
    sa.sa_handler = child_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGCHLD, &sa, NULL);
   struct sockaddr_in example;
   memset(&example, 0, sizeof(example));
   example.sin_family = AF_INET;
   example.sin_port = htons(atoi(argv[1]));
   example.sin_addr.s_addr = htons(INADDR_ANY);

   int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   checkReturn(sockfd>0,1,"socket error");
   int opt = 1;
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
   
   int bind_result = bind(sockfd, (struct sockaddr*)&example, sizeof(example));
   checkReturn(bind_result,0,"bind error");

   int listen_result = listen(sockfd, 5);
   checkReturn(listen_result,0,"listen error");

   for(int i=0;i<5;i++){
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    int accept_socket = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    // checkReturn(accept_socket>0,1,"accept error");
    // the up one is false!
    if (accept_socket < 0 && errno == EINTR){
        i--;
        continue; 
    }
    //----------- multi_process
    int message_pipe[2];
    checkReturn(pipe(message_pipe),0,"pipe error");
    
    pid_t child_pid = fork();
    if(child_pid != 0){
        pid_t save_pid = fork();
        if(save_pid != 0){//主进程
            close(accept_socket);
            printf("client ip: %s,client port %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            continue;
        }
        else{
            //信息保存进程
            close(accept_socket);
            char buffer[1024];
            while(1){
                memset(buffer,0,sizeof(buffer));
                FILE *fp = fopen("./result.txt","a");
                int read_len = read(message_pipe[0],buffer,sizeof(buffer));
                if (read_len == 0){
                    fclose(fp);
                    return 0;
                }
                fwrite(buffer,1,1,fp);
                fclose(fp);
            };
        }
    }
    //-----------
    // int serverStep = 1;
    close(sockfd);
    while(1){
        u_int32_t operator_number = 0;
        readWithCheck(accept_socket,(char*)&operator_number,4,"read operator_number error");
        //debug
        printf("operator_number: %d\n",operator_number);
        //debug
        char buffer[1024] = {0};
        int buffer_number = readWithCheck(accept_socket,buffer,sizeof(uint32_t)*operator_number+sizeof(char),"read buffer error");
        if(buffer_number == 0){ //EOF 和 Q 恰好都是 0 完美解决了Ctrl + C 推出 和 q 推出
            shutdown(accept_socket,SHUT_WR);
            printf("client close the connection\n");
            break;
        }
        char result_buffer[1024] = {0};
        switch (buffer[buffer_number-1]){
            case '+':
                int temp_result = 0;
                for(uint32_t i=0;i<operator_number;i++){
                    temp_result += *(uint32_t*)(buffer+i*sizeof(uint32_t));
                }
                printf("+ temp_result: %d\n",temp_result);
                result_buffer[0] = '+';
                write(message_pipe[1],(void*)result_buffer,1);
                writeWithCheck(accept_socket,(char*)&temp_result,sizeof(uint32_t),"write to client fail!");
                break;
            case '-':
                temp_result = 0;
                temp_result = *(uint32_t*)(buffer) - *(uint32_t*)(buffer+4);
                printf("- temp_result: %d\n",temp_result);
                result_buffer[0] = '-';
                write(message_pipe[1],(void*)result_buffer,1);
                writeWithCheck(accept_socket,(char*)&temp_result,sizeof(uint32_t),"write to client fail!");
                break;
            case '*':
                temp_result = 1;
                for(uint32_t i=0;i<operator_number;i++){
                    temp_result *= *(uint32_t*)(buffer+i*sizeof(uint32_t));
                }
                printf("* temp_result: %d\n",temp_result);
                result_buffer[0] = '*';
                write(message_pipe[1],(void*)result_buffer,1);
                writeWithCheck(accept_socket,(char*)&temp_result,sizeof(uint32_t),"write to client fail!");
                break;
            default:
                printf("operator error!\n");
                strcpy(result_buffer,"operator error!");
                result_buffer[0] = 'E';
                write(message_pipe[1],(void*)result_buffer,1);
                goto end;
                break;
        }

    }
    end:
    close(accept_socket);
    close(sockfd);
    return 0;
   }
    close(sockfd);
    return 0;
}