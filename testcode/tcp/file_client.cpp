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
    if(argc < 4) ErrorHanding("Miss port ip and filename");
    int serv_sd ;
    sockaddr_in serv_adr;
    int read_len ;
    char buff[BUFF_SIZE];
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_addr.s_addr = inet_addr(argv[2]);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));

    FILE* fp = fopen(argv[3],"wb");
    serv_sd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sd == -1) ErrorHanding("socket error");

    if(connect(serv_sd,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1) ErrorHanding("connect error");

    do{
        read_len = read(serv_sd,buff,BUFF_SIZE);
        fwrite((void*)buff,1,read_len,fp);
       // fputs(buff,stdout);
        cout<<"received length : "<<read_len<<endl;
    }while(read_len > 0);
    
    printf("Received file data!");
    
    write(serv_sd,"Thank you",10);

    fclose(fp);

    close(serv_sd);

    return 0;
}