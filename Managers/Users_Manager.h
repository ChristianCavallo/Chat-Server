//
// Created by Noemi Buggea on 21/12/2019.
//

#ifndef CHAT_SERVER_USERS_MANAGER_H
#define CHAT_SERVER_USERS_MANAGER_H
#include <string>
#include <iostream>
#include "../Primitives/User.h"
#include <bsoncxx/types.hpp>

using std::string;
using namespace std;

class Users_Manager {

public:
    Users_Manager() {};

    User *Login(const string &email, const string &password);

    string Registration(User *u);

    void updateUserLastAccess(const string &id);

    bsoncxx::types::b_date getLastAccess(const string &userid);

    User *getUserById(const string &id);

    User *getUserByEmail(const string &email);
};


#endif //CHAT_SERVER_USERS_MANAGER_H
