#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

void ErrorHanding(std::string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
int main(int argc,char** argv){
    int tcp_socket;
    if(argc < 3) ErrorHanding("忘记加参数");
    sockaddr_in servaddr;
    char message[30];
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = inet_addr(argv[2]);
    tcp_socket = socket(PF_INET,SOCK_STREAM,0);
    if(tcp_socket == -1) ErrorHanding("socket error");
    if(connect(tcp_socket,(sockaddr*)&servaddr,sizeof(servaddr))==-1) ErrorHanding("connect error");
    read(tcp_socket,message,sizeof(message));
    printf("%s \n",message);
    
    close(tcp_socket);
    printf("close the socket");
    return 0;
}
