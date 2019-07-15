# include <iostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>

# include <netdb.h>

using namespace std;

const int BUFF_SIZE = 100 ; 

int main(int argc,char** argv){
    if(argc < 2){
        printf("please input some domain \n");
        exit(1);
    }
    hostent* res;
    for(int i = 1; i< argc; i++){
        printf("domain %d: %s\n",i,argv[i]);
        res = gethostbyname(argv[i]);
        if(!res){
            printf("get host error\n");
            exit(1);
        }
        printf("official name: %s\n",res->h_name);
        printf("addres length: %d\n",res->h_length);
        printf("host address type: %d\n",res->h_addrtype);
        printf("host aliases(其他域名):\n");
        int count = 0;
        while(res->h_aliases[count]!=NULL){
            printf("%s\n",res->h_aliases[count]);
            count++;
        }
        printf("该域名其他IP地址:\n");
        count = 0;
        while(res->h_addr_list[count]!=NULL){
            printf("%s\n",inet_ntoa(*(in_addr*)res->h_addr_list[count]));
            count++;
        }
        printf("\n-----------------------\n");
    }   

    return 0;
}