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
    int tcp_socket,str_len;
    if(argc < 3) ErrorHanding("忘记加参数");
    sockaddr_in servaddr;
    int recv_len=0,recv_chunk=0;
    char message[BUFF_SIZE];
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = inet_addr(argv[2]);
    tcp_socket = socket(PF_INET,SOCK_STREAM,0);
    if(tcp_socket == -1) ErrorHanding("socket error");
    if(connect(tcp_socket,(sockaddr*)&servaddr,sizeof(servaddr))==-1) ErrorHanding("connect error");
    while(true){
        fputs("Input message(Q to quit): ",stdout);
        fgets(message,BUFF_SIZE,stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")){
            break;
        }
        str_len = write(tcp_socket,message,strlen(message));
        
        while(recv_len < str_len){
            recv_chunk = read(tcp_socket,&message[recv_len],BUFF_SIZE-1);
            if(recv_chunk == -1)
                ErrorHanding("read data fail");
            recv_len+=recv_chunk;
        }
        //最后补一个0因为我们没有发送0;
        message[str_len] = 0;
        recv_len = 0;
        printf("Message from server : %s",message);
    }
    
    close(tcp_socket);
    printf("close the socket");
    return 0;
}
