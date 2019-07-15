# include <iostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <cstring>
using namespace std;

const int BUFF_SIZE = 100 ; 

int main(int argc,char** argv){
    if(argc < 2){
        printf("please input some domain \n");
        exit(1);
    }
    hostent* host;
    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);
    if(!host){
        printf("host error\n");
        exit(1);
    }
    printf("official name: %s\n",host->h_name);
    printf("addres length: %d\n",host->h_length);
    printf("host address type: %d\n",host->h_addrtype);
    printf("host aliases(其他域名):\n");
    int count = 0;
    while(host->h_aliases[count]!=NULL){
        printf("%s\n",host->h_aliases[count]);
        count++;
    }
    printf("该域名其他IP地址:\n");
    count = 0;
    while(host->h_addr_list[count]!=NULL){
        printf("%s\n",inet_ntoa(*(in_addr*)host->h_addr_list[count]));
        count++;
    }
    printf("\n-----------------------\n");

    return 0;
}