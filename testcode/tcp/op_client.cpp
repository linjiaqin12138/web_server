#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;
const int BUFF_SIZE = 1024;
const int RLT_SIZE = 4;
const int OPSZ = 4;
void ErrorHanding(string mess){
    fputs(mess.c_str(),stderr);
    fputc('\n',stderr);
    exit(1);
}
int main(int argc,char** argv){
    int clnt_socket;
    int opnd_cnt;
    int result;
    sockaddr_in clnt_addr;
    if(argc < 3) ErrorHanding("Miss parameter");
    memset(&clnt_addr,0,sizeof(clnt_addr));
    char opmsg[BUFF_SIZE];
    clnt_addr.sin_addr.s_addr = inet_addr(argv[2]);
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_port = atoi(argv[1]);
    clnt_socket = socket(AF_INET,SOCK_STREAM,0);
    if(clnt_socket == -1) ErrorHanding("scoket fail");
    if((connect(clnt_socket,(sockaddr*)&clnt_addr,sizeof(clnt_addr)))==-1) ErrorHanding("connect error");
    else printf("Connecting ...\n");
    fputs("Operand count:",stdout);
    scanf("%d",&opnd_cnt);
    opmsg[0] = (char)opnd_cnt;
    for(int i=0;i<opnd_cnt;i++){
        printf("Operand %d: ",i+1);
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);
    }
    fgetc(stdin);
    fputs("Opeator: ",stdout);
    scanf("%c",&opmsg[opnd_cnt*OPSZ+1]);
    //include the final 0 ? 
    write(clnt_socket,opmsg,opnd_cnt*OPSZ+2);
    read(clnt_socket,&result,RLT_SIZE);
    cout<<result<<endl;
    return 0;
}