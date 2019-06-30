#include <iostream>
#include "server.h"
using namespace std;

int main(int argc,char** argv){
    try{
        My_Web::TCP_Server Server(3333);
        string mess = "Hello world!";
        Server.send(mess);
        Server.close();
    }catch(My_Web::Error& err){
        err.showMessage();
    }
    return 0;
}