// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include "Socket/Server.h"
#include <thread>
using namespace std;

void ciao(){
    cout << "Ciao";
}

int main(void)
{

    Server* s = new Server();
    s->start();

    cin.get();

}
