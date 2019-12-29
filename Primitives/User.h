//
// Created by Noemi Buggea on 14/12/2019.
//

#ifndef CHAT_SERVER_USER_H
#define CHAT_SERVER_USER_H

#include <string>

using namespace std;

class User {
private:


public:
    string id;
    string name;
    string surname;
    string email;
    string password;

    User(string id, string name, string surname, string email, string password) {
        this->id = id;
        this->name = name;
        this->surname = surname;
        this->email = email;
        this->password = password;
    }

    User() {}

    const string &getName() const {
        return name;
    }

    const string &getEmail() const {
        return email;
    }

    const string &getPassword() const {
        return password;
    }

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
