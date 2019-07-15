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
    int serv_socket;
    sockaddr_in clnt_addr;
    char message[BUFF_SIZE] = "Hello world!";
    if(argc < 3) ErrorHanding("miss parameter ");

    memset(&clnt_addr,0,sizeof(clnt_addr));

    clnt_addr.sin_addr.s_addr = inet_addr(argv[2]) ;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_port = atoi(argv[1]);

    serv_socket = socket(PF_INET,SOCK_STREAM,0);
    if(connect(serv_socket,(sockaddr*)&clnt_addr,sizeof(clnt_addr)) == -1) ErrorHanding("connet fail");
    write(serv_socket,message,strlen(message));
    cout<<message<<endl;
    write(serv_socket,message,strlen(message));
    cout<<message<<endl;
    write(serv_socket,message,strlen(message));
    cout<<message<<endl;
    write(serv_socket,message,strlen(message));
    cout<<message<<endl;
    close(serv_socket);
    return 0;
}