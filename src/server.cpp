#include "server.h"

My_Web::TCP_Server::TCP_Server(int port,std::string ip_addr){
    mport = port;
    memset(&(this->ip_addr),0,sizeof(this->ip_addr));
    
    this->ip_addr.sin_family = AF_INET;
    this->ip_addr.sin_port = htons(port);
    //this->ip_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    this->ip_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcp_sock = socket(PF_INET,SOCK_STREAM,0);
    if(tcp_sock == -1) throw Error("fail to create socket");
    if(bind(tcp_sock,(sockaddr*)&this->ip_addr,sizeof(this->ip_addr))==-1)
        throw Error("fail to bind the socket with ip_address");
    if(listen(tcp_sock,5)==-1) throw Error("fail to listen\n");
    socklen_t clnt_size = sizeof(this->clnt_addr);
    clnt_sock = accept(tcp_sock,(sockaddr*)&this->clnt_addr,&clnt_size);
    if(clnt_sock == -1)
        throw Error("fail to accept");   
}
void My_Web::TCP_Server::close(){
    ::close(this->tcp_sock);
    ::close(this->clnt_sock);
}
uint8_t My_Web::TCP_Server::send(std::string& mess){
    ::write(tcp_sock,mess.c_str(),30);
    return sizeof(mess.c_str());
}

My_Web::TCP_Client::TCP_Client(int port,std::string ip_addr){
    mport = port;
    memset(&this->ip_addr,0,sizeof(this->ip_addr));
    this->ip_addr.sin_family = AF_INET;
    this->ip_addr.sin_port = htons(port);
    this->ip_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    tcp_sock = socket(PF_INET,SOCK_STREAM,0);
    if(tcp_sock == -1) throw Error("fail to create socket");
    if(connect(tcp_sock,(sockaddr*)&this->ip_addr,sizeof(this->ip_addr))==-1)
        throw Error("fail to connect the socket with ip_address");
    
}
void My_Web::TCP_Client::close(){
    ::close(this->tcp_sock);
}
std::string My_Web::TCP_Client::recv(){
    char mess[30];
    int strlen ;
    strlen = ::read(tcp_sock,mess,sizeof(mess)-1);
    if(strlen == -1) throw Error("fail to read the data.");
    printf("%s",mess);
    return std::string(mess);
}