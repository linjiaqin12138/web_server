#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string> 
namespace My_Web{
    class Error{
        public:
            Error(std::string mess){
                this->mess = mess;
            }
            void showMessage(){
                fputs(mess.c_str(),stderr);
            }
        private:
            std::string mess;
    };
    class TCP_Server{
        public:
            TCP_Server(int port,std::string ip_addr = "127.0.0.1");
            
            uint8_t send(std::string mess);
            
            void close();
        private:
            int mport;
            sockaddr_in ip_addr;
            int tcp_sock;
            sockaddr_in clnt_addr;
            int clnt_sock;

    };
    class TCP_Client{
        public:
            TCP_Client(int port,std::string ip_addr);
            
            std::string recv();
            
            void close();
        private:
            int mport;
            sockaddr_in ip_addr;
            int tcp_sock;
            
    };
}
