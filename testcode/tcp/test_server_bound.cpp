#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;
void ErrorHanding(string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
const int BUFF_SIZE = 1024;
int main(int argc,char** argv){
    int tcp_socket,clnt_socket;
    sockaddr_in serv_socket,clnt_addr;
    socklen_t clnt_size = sizeof(clnt_socket);
    memset(&serv_socket,0,sizeof(serv_socket));
    char message[BUFF_SIZE];
    serv_socket.sin_addr.s_addr = htons(INADDR_ANY);
    serv_socket.sin_family = AF_INET;
    serv_socket.sin_port = atoi(argv[1]);

    tcp_socket = socket(PF_INET,SOCK_STREAM,0);

    if(tcp_socket == -1) ErrorHanding("scoket error");
    if((bind(tcp_socket,(sockaddr*)&serv_socket,sizeof(serv_socket)))==-1){
        ErrorHanding("bind error");
    }
    if(listen(tcp_socket,5) == -1) ErrorHanding("listen error");
    clnt_socket = accept(tcp_socket,(sockaddr*)&clnt_addr,&clnt_size);
    if(clnt_socket == -1) ErrorHanding("accept error");
    else printf("Connect successfully\n");
    sleep(5);
    read(clnt_socket,message,sizeof(message));
    message[strlen(message)] = 0;
    cout<<message<<endl;
    
    close(clnt_socket);
    close(tcp_socket);
    return 0;
}