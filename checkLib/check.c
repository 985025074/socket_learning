#include "check.h"
#include <stdlib.h>
void checkReturn(int returnVal,int expected,const char* errorMsg){
    if (returnVal != expected)
    {
        printf("Error: expected %d, but got %d\n", expected, returnVal);
        printf("%s\n", errorMsg);
        exit(1);
    }
}
void checkArgs(int getArgs,int expectedArgs,const char *errorMsg){
    if (getArgs != expectedArgs)
    {
        printf("Error: expected %d arguments, but got %d\n", expectedArgs, getArgs);
        printf("%s\n", errorMsg);
        exit(1);
    }
}
void checkTrue(int evaluations,const char* error_ms){
    checkReturn(evaluations,1,error_ms);
}
