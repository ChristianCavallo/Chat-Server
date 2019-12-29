//
// Created by Noemi Buggea on 21/12/2019.
//

#ifndef CHAT_SERVER_USERS_MANAGER_H
#define CHAT_SERVER_USERS_MANAGER_H
#include <string>
#include <iostream>
#include "User.h"

using std::string;
using namespace std;

class Users_Manager {

public:
    Users_Manager(){};

    User *Login(const string &email, const string &password);

    string Registration(User *u);
};


#endif //CHAT_SERVER_USERS_MANAGER_H
