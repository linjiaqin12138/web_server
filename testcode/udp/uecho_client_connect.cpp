#include <iostream>
#include <cstdio>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <string>
const int BUFF_SIZE = 1024;
void ErrorHanding(std::string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
int main(int argc,char** argv){
    if(argc<3) ErrorHanding("miss port and ip address");
    char message[BUFF_SIZE];
    char mess2[BUFF_SIZE];
    int serv_sock;
    int str_len;
    sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_sz = sizeof(clnt_addr);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[2]);
    serv_addr.sin_port = htons(atoi(argv[1]));
      
    serv_sock = socket(PF_INET,SOCK_DGRAM,0);
    if(serv_sock == -1) ErrorHanding("socket error");
    if(connect(serv_sock,(sockaddr*)&serv_addr,sizeof(serv_addr)) == -1) ErrorHanding("connect error");

    while(1){
        fputs("Insert message(q to quit)",stdout);
        fgets(message,sizeof(message),stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")) break;
        write(serv_sock,message,strlen(message)+1);
        sleep(2);
        str_len = read(serv_sock,mess2,BUFF_SIZE);
        printf("received %d" ,str_len);
        mess2[str_len] = 0;
        printf("Message from server:%s\n",mess2); 
    }
    close(serv_sock);
    return 0;
}
