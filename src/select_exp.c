#include "normal_include.h"
int main(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    
    while(1){
        struct  timeval timeval_;
        timeval_.tv_sec = 1;
        timeval_.tv_usec = 0;
        FD_SET(0, &readfds);
        int number = select(1,&readfds,NULL,NULL,&timeval_);
        if(number == -1){
            return 0;
        }
        else if (number == 0){
            printf("timeout!!\n");
        }
        if(FD_ISSET(0,&readfds) && number == 1){
            printf("input detected \n");
            getchar();
        }

    }
    return 0;
}