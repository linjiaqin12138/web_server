#include <iostream>
#include "server.h"
using namespace std;

int main(int argc,char** argv){
    string mess = "Hello world!";
    try{
        My_Web::TCP_Server Server(3333);
        Server.send(mess);
        Server.close();
    }catch(My_Web::Error& err){
        err.showMessage();
    }
    return 0;
}