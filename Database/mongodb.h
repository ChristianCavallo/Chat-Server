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
private:
    instance* inst;
    client* client;
public:
    database db;
    collection coll;

    Mongodb() {
        inst = new instance();
        client = new mongocxx::client(uri{});

        db = client->database("testdb");
        cout << "Mongo connected\n";
    }

    virtual ~Mongodb();


    void CreateCollection(string name);
};


#endif //CHAT_SERVER_MONGODB_H
