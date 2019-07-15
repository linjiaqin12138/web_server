#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc,char** argv){
    int sock;
    int send_buf,rev_buf,state;
    socklen_t len;
    sock = socket(PF_INET,SOCK_STREAM,0);
    len = sizeof(send_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&send_buf,&len);
    if(state) exit(1);
    len = sizeof(rev_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rev_buf,&len);
    if(state) exit(1);
    printf("Input buffer size: %d\n",rev_buf);
    printf("Output buffer size: %d\n",send_buf);
    len = sizeof(send_buf);
    send_buf = 5000;
    state = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&send_buf,len);
    if(state) exit(1);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&send_buf,&len);
    if(state) exit(1);
    printf("Output buffer size: %d\n",send_buf);
    return 0;
}