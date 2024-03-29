#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
const int BUFF_SIZE = 30;
void ErrorHanding(std::string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
int main(int argc,char** argv){
    int tcp_socket,clnt_socket;
    if(argc < 2) ErrorHanding("忘记加参数");
    sockaddr_in servaddr,clntaddr;
    char message[BUFF_SIZE];
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcp_socket = socket(PF_INET,SOCK_STREAM,0);
    int option = 1;
    if(setsockopt(tcp_socket,SOL_SOCKET,SO_REUSEADDR,(void*)&option,sizeof(option)));
    if(tcp_socket == -1) ErrorHanding("socket error");
    socklen_t sock_size = sizeof(clntaddr);
    if(bind(tcp_socket,(sockaddr*)&servaddr,sizeof(servaddr))==-1) ErrorHanding("Bind errpr");
    if(listen(tcp_socket,5) == -1) ErrorHanding("listen error");
    for(int i=0;i<5;i++){
        clnt_socket = accept(tcp_socket,(sockaddr*)&clntaddr,&sock_size);
        if(clnt_socket == -1) ErrorHanding("accept error");
        else
            printf("Connecting to %d client\n",i+1);
        int str_len;
        
        while((str_len = read(clnt_socket,message,BUFF_SIZE))!=0)
            write(clnt_socket,message,str_len);
        close(clnt_socket);
    }
    
    close(tcp_socket);
    printf("close the socket");
    return 0;
}