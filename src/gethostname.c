#include "normal_include.h"
#include <netdb.h>
int main(){
    struct hostent host;

    host = *gethostbyname("www.baidu.com");
// char* h_name official name
//char ** h_aliases 别名列表
//int h_addrtype 地址类型 地址族
//int h_length 地址长度 ipv4为4，ipv6为16
//char ** h_addr_list ip 列表，注意实际类型为in_addr

    printf("h_name:%s\n",host.h_name);
    for(char ** first = host.h_aliases; *first!= NULL; first++){
        printf("alias:%s\n",*first);
    }
    printf("h_addrtype:%d\n",host.h_addrtype);
    printf("h_length:%d\n",host.h_length);
    for(char ** addr = host.h_addr_list; *addr != NULL; addr++){
        printf("ip:%s\n",inet_ntoa(*((struct in_addr*)*addr)));
    }   
    return 0;
}