// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include "Commands/Command.h"
#include "core/Dispatcher.h"


using namespace std;


int main() {

    Mongodb::getInstance(); //Prima inizializzazione del db
    Dispatcher::getInstance(); //Lazy initialization


    //creo un utente
    User *p = new User("", "pollo", "pollone", "pollo@live.it", "12345");
    //inserisco l'utente nella lista users
    cout << Mongodb::getInstance().addUser(p) << "\n";

    delete p;

    string id = "5e091e5575020000b7007312";




    /*
    if(user != nullptr){
        cout << "utente trovato\n"; //si ma era più giusto che diceva utente non trovato e poi inserito... ma sta cercando due utenti diversi
        delete user;
    } else {
        cout << "utente non trovato\n";
    }*/

    /*
    User* u = new User("", "Noemi", "Buggea", "buggfix@live.it",
            "12345");
    Mongodb::getInstance().addUser(u);

    delete u;
    */


    auto *server = new Server();
    server->start();

    Dispatcher::getInstance().server = server;

    Dispatcher::getInstance().logoutUser(id);
    cout << Dispatcher::getInstance().getUserStatus(id) << "\n";
    cin.get();

}