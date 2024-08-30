#include "check.h"
#include <stdlib.h>
#include <unistd.h>
void checkReturn(int returnVal,int expected,const char* errorMsg){
    if (returnVal != expected)
    {
        printf("Error: expected %d, but got %d\n", expected, returnVal);
        printf("%s\n", errorMsg);
        perror("Perror");
        exit(1);
    }
}
void checkArgs(int getArgs,int expectedArgs,const char *errorMsg){
    if (getArgs != expectedArgs)
    {
        printf("Error: expected %d arguments, but got %d\n", expectedArgs, getArgs);
        printf("%s\n", errorMsg);
        perror("Perror");
        exit(1);
    }
}
void checkTrue(int evaluations,const char* error_ms){
    checkReturn(evaluations,1,error_ms);
}
int writeWithCheck(int fd,const char* data,int size,const char* error_ms){
    int write_result = write(fd,data,size);
    checkTrue(write_result>=0,error_ms);
    return write_result;
}
int readWithCheck(int fd,char* data,int size,const char* error_ms){
    int read_result = read(fd,data,size);
    checkTrue(read_result>=0,error_ms);
    return read_result;
}
