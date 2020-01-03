//
// Created by Noemi Buggea on 14/12/2019.
//

#ifndef CHAT_SERVER_USER_H
#define CHAT_SERVER_USER_H

#include <string>
#include <bsoncxx/types.hpp>
#include <chrono>

using namespace std;

class User {
private:


public:
    string id;
    string name;
    string surname;
    string email;
    string password;
    bsoncxx::types::b_date lastaccess{std::chrono::system_clock::now()};

    User(const string &id, const string &name, const string &surname, const string &email, const string &password,
         const bsoncxx::types::b_date &lastaccess) : id(id), name(name), surname(surname), email(email),
                                                     password(password), lastaccess(lastaccess) {}

    User(const string &id, const string &name, const string &surname, const string &email, const string &password) : id(
            id), name(name), surname(surname), email(email), password(password) {}

    //questi li genera in automatico... praticamente possiamo cambiare il comportamento degli operatori tipo ==
    bool operator==(const User &rhs) const {
        //gli sto dicendo che quando faccio user1 == user2 deve confrontare id e email per dire se sono lo stesso utente
        return id == rhs.id &&
               email == rhs.email;
    }

    bool operator!=(const User &rhs) const {
        return !(rhs == *this);
    }


};


#endif //CHAT_SERVER_USER_H
