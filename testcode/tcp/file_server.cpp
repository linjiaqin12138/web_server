#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
const int BUFF_SIZE = 30;

void ErrorHanding(string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char** argv){
    int serv_sd,clnd_sd;
    FILE* fd;
    char buff[BUFF_SIZE];
    int read_cnt;

    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc<3) ErrorHanding("Miss port and filename");

    fd = fopen(argv[2],"rb");

    serv_sd = socket(PF_INET,SOCK_STREAM,0);

    if(serv_sd == -1) ErrorHanding("socket error");
    memset(&serv_adr,0,sizeof(serv_adr));

    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sd,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
        ErrorHanding("bind error");
    if(listen(serv_sd,5) == -1) ErrorHanding("listen error");
    clnt_adr_sz = sizeof(clnt_adr);
    clnd_sd = accept(serv_sd,(sockaddr*)&clnt_adr,&clnt_adr_sz);
    while(1){
        read_cnt = fread((void*)buff,1,BUFF_SIZE,fd);
        if(read_cnt < BUFF_SIZE){
            write(clnd_sd,buff,read_cnt);
            break;
        }
        write(clnd_sd,buff,BUFF_SIZE);
    }
    //sleep(5);
    shutdown(clnd_sd,SHUT_WR);
    puts("transfer finished ! ");
    read(clnd_sd,buff,BUFF_SIZE);
    printf("message from client: %s\n",buff);
    close(clnd_sd);
    close(serv_sd);
    fclose(fd);

    return 0;
}