//
// Created by Noemi Buggea on 21/12/2019.
//

#include "Users_Manager.h"
#include "../Database/mongodb.h"

User *Users_Manager::Login(const string &email, const string &password) {
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
            cout << u->name << " " << u->surname << " correctly logged\n";
            return u;
        }
        cout << u->name << " " << u->surname << " -> wrong credentials!\n";
        return nullptr;
    }

    cout << "Can't login, user doesn't exist!\n";
    return nullptr;
}

string Users_Manager::Registration(User *u) {
    /* ========REGISTRAZIONE=====
    * 1) la funzione di registrazione prende una serie di parametri: in questo caso un user
    * 2) la funzione crea una nuova classe User* u, con tutti i parametri
    * 3) viene richiamata la funzione addUser(u) del mongodb
    * 4) se l'utente viene inserito, allora ritorna True, altrimenti False.
    * 5) per il passo 4) è necessario modificare il tipo di ritorno della funzione, attualmente impostato su void.
    */

    if (u->name.empty() || u->name.size() > 20) {

        return "Invalid name.";
    }

    if (u->surname.empty() || u->surname.size() > 20) {

        return "Invalid surname.";
    }

    if (u->email.size() < 6 || u->email.find('@') == std::string::npos || u->email.find('.') == std::string::npos) {
        return "Invalid email.";
    }

    if (u->password.empty() || u->password.size() != 32) {

        return "Invalid password.";
    }


    return Mongodb::getInstance().addUser(u);

}

void Users_Manager::updateUserLastAccess(const string &id) {
    Mongodb::getInstance().UpdateUserLastAccess(id);
}

long long Users_Manager::getLastAccess(const string &userid) {
    return Mongodb::getInstance().getLastAccess(userid);
}

User* Users_Manager::getUserById(const string & id){

    return Mongodb::getInstance().getUserById(id);

}


