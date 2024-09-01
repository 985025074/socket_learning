#include "normal_include.h"

int main(){
    int mypipe[2];
        checkReturn(pipe(mypipe),0,"pipe error");
        //write 1,read 0
        pid_t son = fork();
        char wait_to_write[] = "shiyicong";
        if(son == 0){
            writeWithCheck(mypipe[1],wait_to_write,sizeof(wait_to_write),"son write error");
            sleep(5);
            char read_buf[100];
            readWithCheck(mypipe[0],read_buf,9999, "son read error");
            printf("son read: %s\n",read_buf);
        }
        else{
            char read_buf[100];
            readWithCheck(mypipe[0],read_buf,9999, "father read error");
            close(mypipe[0]);
            printf("father read: %s\n",read_buf);
            writeWithCheck(mypipe[1],wait_to_write,sizeof(wait_to_write),"father write error");
            close(mypipe[1]);

        }
    return 0;
}