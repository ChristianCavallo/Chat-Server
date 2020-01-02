//
// Created by chryc on 11/12/2019.
//

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include "../Primitives/User.h"
#include "../Primitives/Chat.h"
#include <vector>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using namespace mongocxx;
using namespace std;

#ifndef CHAT_SERVER_MONGODB_H
#define CHAT_SERVER_MONGODB_H


class Mongodb {

public:
    static Mongodb &getInstance() {
        static Mongodb instance;
        return instance;
    }


public:
    Mongodb(Mongodb const &) = delete;

    void operator=(Mongodb const &) = delete;

private:
    instance *inst;
    mongocxx::client *client;
    database db;
    collection coll;

    Mongodb() {
        inst = new instance();
        client = new mongocxx::client(uri{});

        db = client->database("testdb");
        cout << "Mongo connected\n";
    }

    virtual ~Mongodb();

public:
    User *getUser(const string &email);

    string Mongodb::addUser(User *u);

    string Mongodb::CreateChat(Chat *ch);

    void UpdateUserLastAccess(const string &id);

    long long getLastAccess(const string &userid);

    vector<Chat *> getChats(const string &userid);

    Chat * getChat(Chat* c);

    Chat *getChatById(const string &chatId);

    Chat *updateMessage(const string &chatId, Message* m);

    User *getUserById(const string &id);
};


#endif //CHAT_SERVER_MONGODB_H
