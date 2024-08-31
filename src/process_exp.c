#include "normal_include.h"

void alarmer(int){
    printf("Alarm signal!\n");
    alarm(2);
}
void ctrl_c(int){
    printf("Ctrl-C signal!\n");
    exit(0);
}
int main(){
    signal(SIGALRM, alarmer);
    signal(SIGINT, ctrl_c);
    alarm(2);
    for(int i = 1;i <= 5;i++){
        printf("This is the %d-th time.\n", i);
        sleep(100);
    }
    return 0;
}