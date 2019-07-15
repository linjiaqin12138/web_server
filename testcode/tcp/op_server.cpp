#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
const int BUFF_SIZE = 1024;
void ErrorHanding(string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
int calculate(int opnd_cnt,int* opinfo,char op){
    int result = opinfo[0],i;
    switch(op){
        case '+':
            for(i=1;i<opnd_cnt;i++) result+=opinfo[i];
            break;
        case '-':
            for(i=1;i<opnd_cnt;i++) result-=opinfo[i];
            break;
        case '*':
            for(i=1;i<opnd_cnt;i++) result*=opinfo[i];
            break;
    }
    return result;
}
int main(int argc,char** argv){
    int serv_socket,clnt_socket;
    sockaddr_in serv_addr,clnt_addr;
    int opnd_cnt;
    char opinfo[BUFF_SIZE];
    int recv_len = 0,recv_cnt = 0;
    int result = 0;
    if(argc < 2) ErrorHanding("Miss port");
    memset(&serv_addr,0,sizeof(serv_addr));

    serv_socket = socket(PF_INET,SOCK_STREAM,0);
    if(serv_socket == -1) ErrorHanding("socket fail");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = atoi(argv[1]);
    socklen_t serv_size = sizeof(serv_addr);
    socklen_t clnt_size = sizeof(clnt_addr);
    if((bind(serv_socket,(sockaddr*)&serv_addr,serv_size) == -1)) ErrorHanding("bind fail");
    listen(serv_socket,5);
    for(int i=0;i<5;i++){
        opnd_cnt = 0;
        clnt_socket = accept(serv_socket,(sockaddr*)&serv_addr,&clnt_size);
        if(clnt_socket == -1) ErrorHanding("accept fail");
        read(clnt_socket,&opnd_cnt,1);

        recv_len = 0;

        if(recv_len < (opnd_cnt*4)+1){
            recv_cnt += read(clnt_socket,&opinfo[recv_len],BUFF_SIZE -1 );
            recv_len += recv_cnt;
        } 
        result = calculate(opnd_cnt,(int*) opinfo,opinfo[recv_len-1]);

        write(clnt_socket,&result,sizeof(result));

        close(clnt_socket);

    }
    printf("Close the socket\n");
    close(serv_socket);

    return 0;
}