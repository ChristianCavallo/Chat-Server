//
// Created by Noemi Buggea on 21/12/2019.
//

#include "Users_Manager.h"
#include "../Database/mongodb.h"

User *Users_Manager::Login(string email, string password) {
    /*
     * ======LOGIN======
     * 1) la funzione prende come parametri: email e password
     * 2) la funzione richiama la funzione getUser(email) del mongodb
     * 3) se l'utente viene trovato, confrontare i campi password
     * 4) se corrispondono, la funzione ritorna l'utente User, altrimenti nullptr
     **/

    User *u = Mongodb::getInstance().getUser(email);

    if (u != nullptr) {
        if (email == u->email && password == u->password) {
            cout << u->getName() << " " << u->surname << " correctly logged\n";
            return u;
        }
        cout << u->getName() << " " << u->surname << " -> wrong credentials!\n";
        return nullptr;
    }

    cout << "Can't login, user doesn't exist!\n";
    return nullptr;
}

int Users_Manager::Registration(User *u) {
    /* ========REGISTRAZIONE=====
    * 1) la funzione di registrazione prende una serie di parametri: in questo caso un user
    * 2) la funzione crea una nuova classe User* u, con tutti i parametri
    * 3) viene richiamata la funzione addUser(u) del mongodb
    * 4) se l'utente viene inserito, allora ritorna True, altrimenti False.
    * 5) per il passo 4) è necessario modificare il tipo di ritorno della funzione, attualmente impostato su void.
    */
    // addUser vuole un utente, Registration ha come parametro l'utente, il dispatcher procura l'utente a registration
    // quindi Dispatcher crea u --> Registration(u) --> addUser(u)
    //se addUser(U) registra allora ritorna true, altrimenti false
    if(Mongodb::getInstance().addUser(u)){ //vuol dire true
        return 1; // è registrato...
    }
    return 0; // se va qui non lo è... devo aggiungerlo...o qualche problema?
}


