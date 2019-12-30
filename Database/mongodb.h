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
    //ho capito quello che dici tu... infatti ne anche io ero convint.... ma sicocme facendo mongodb. non succedeva nt.... sono nadata nel apllone pe
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
    User *getUser(const string &email); //per esempio... puoi farla anche diversamente

    //Voglio che capisci solo questa cosa. La funzione addUser aggiunge un utente. ma al solito, come facciamo a sapere se lo ha
    //fattpo o no? un ritorno di variabile? si, di che tipo? bool va bene. esegui
    string Mongodb::addUser(User *u);

    void UpdateUserLastAccess(const string &id);

    long long getLastAccess(const string &userid);

    vector<Chat *> getChat(const string &userid);

};


#endif //CHAT_SERVER_MONGODB_H
