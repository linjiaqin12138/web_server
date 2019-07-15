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
    char mess1[] = "Hi";
    char mess2[] = "I am DUP host";
    char mess3[] = "Nice to meet you";
    int serv_sock;
    int str_len;
    sockaddr_in clnt_addr;
    socklen_t clnt_addr_sz = sizeof(clnt_addr);
    memset(&clnt_addr,0,sizeof(clnt_addr));
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(argv[2]);
    clnt_addr.sin_port = htons(atoi(argv[1]));
    serv_sock = socket(PF_INET,SOCK_DGRAM,0);
    if(serv_sock == -1) ErrorHanding("socket error");

    sendto(serv_sock,mess1,sizeof(mess1),0,(sockaddr*)&clnt_addr,sizeof(clnt_addr));
    sendto(serv_sock,mess2,sizeof(mess2),0,(sockaddr*)&clnt_addr,sizeof(clnt_addr));
    sendto(serv_sock,mess3,sizeof(mess3),0,(sockaddr*)&clnt_addr,sizeof(clnt_addr));

    close(serv_sock);
    return 0;

}