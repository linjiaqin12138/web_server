#include "server.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    try{
         My_Web::TCP_Client client(3333,"127.0.0.1");
        string res = client.recv();
        cout<<res<<endl;
        client.close();
    }catch(My_Web::Error& err){
        err.showMessage();
    }
    return 0;
}