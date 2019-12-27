// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include "Commands/Command.h"
#include "core/Dispatcher.h"
#include "Managers/User.h"
#include "Managers/Users_Manager.h"

using namespace std;


int main() {



    Mongodb::getInstance(); //Prima inizializzazione del db
    Dispatcher::getInstance(); //Lazy initialization

    /*
    //creo un utente
    User *p = new User("","tigro", "bello", "tigro@live.it", "abcd123");
    //inserisco l'utente nella lista users
    Mongodb::getInstance().addUser(p);
    //verifico se l'iscrizione è andata a buon fine
    int a= Users_Manager().Registration(p);
    cout << a;
    //verifico il login
    Users_Manager().Login(const_cast<string &>(p->getEmail()), const_cast<string &>(p->getPassword()));

    delete p;
    */

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


    Server *server = new Server();
    server->start();

    cin.get();

}