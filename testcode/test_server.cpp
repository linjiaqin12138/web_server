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
    int tcp_socket,clnt_socket;
    if(argc < 2) ErrorHanding("忘记加参数");
    sockaddr_in servaddr,clntaddr;
    char message[] = "Hello world!";
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcp_socket = socket(PF_INET,SOCK_STREAM,0);
    if(tcp_socket == -1) ErrorHanding("socket error");
    
    if(bind(tcp_socket,(sockaddr*)&servaddr,sizeof(servaddr))==-1) ErrorHanding("Bind errpr");
    if(listen(tcp_socket,5) == -1) ErrorHanding("listen error");
    socklen_t sock_size = sizeof(clntaddr);
    clnt_socket = accept(tcp_socket,(sockaddr*)&clntaddr,&sock_size);
    if(clnt_socket == -1) ErrorHanding("accept error");
    write(clnt_socket,message,sizeof(message));
    close(tcp_socket);
    close(clnt_socket);
    printf("close the socket");
    return 0;
}