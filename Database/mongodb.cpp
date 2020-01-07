//
// Created by chryc on 11/12/2019.
//

#include "mongodb.h"
#include "../Commands/Command.h"
#include "../Primitives/User.h"
#include <bsoncxx/types.hpp>
#include <chrono>

using namespace std;

Mongodb::~Mongodb() {
    delete inst;
    delete pool;

}

//==========================User=========================//

string Mongodb::addUser(User *u) {     //Passo l'utente ovverò tutti i campi creati

    User *u2 = getUser(u->email);
    if (u2 != nullptr) {
        delete u2; //xke dentro l'if, u2 è un vero utente.. e va cancellato xke l'ho allocato con il new
        return "User already exist.";
    }


    auto client = pool->acquire();
    this->coll = client->database("testdb")["users"];

    auto builder = bsoncxx::builder::stream::document{};
    auto now = std::chrono::system_clock::now();
    bsoncxx::types::b_date dt{now};
    bsoncxx::document::value doc_value = builder

            << "name" << u->name
            << "surname" << u->surname
            << "email" << u->email
            << "password" << u->password
            << "last-access" << dt
            << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_value.view();
    coll.insert_one(view);
    cout << "Utente inserito \n";
    //Deve tornare True;
    return "ok";
}

User *Mongodb::getUser(const string &email) {

    //SELECT * FROM chats WHERE partecipants =
    auto client = pool->acquire();
    this->coll = client->database("testdb")["users"];
    //coll = this->db["users"];                                           // SELECT * FROM users WHERE email = 'email'
    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "email" << email << finalize);
    if (result) {

        string email = result->view()["email"].get_utf8().value.to_string();
        string name = result->view()["name"].get_utf8().value.to_string();
        string surname = result->view()["surname"].get_utf8().value.to_string();
        string password = result->view()["password"].get_utf8().value.to_string();

        string id = result->view()["_id"].get_oid().value.to_string();
        bsoncxx::types::b_date dt = result->view()["last-access"].get_date();
        User *u = new User(id, name, surname, email, password, dt);
        return u;

    }

    return nullptr;
}

User *Mongodb::getUserById(const string &id) {

    //SELECT * FROM chats WHERE partecipants =
    auto client = pool->acquire();
    this->coll = client->database("testdb")["users"];
    //coll = this->db["users"];                                           // SELECT * FROM users WHERE email = 'email'
    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "_id" << bsoncxx::oid{stdx::string_view{id}} << finalize);
    if (result) {

        string email = result->view()["email"].get_utf8().value.to_string();
        string name = result->view()["name"].get_utf8().value.to_string();
        string surname = result->view()["surname"].get_utf8().value.to_string();
        string password = result->view()["password"].get_utf8().value.to_string();

        string id = result->view()["_id"].get_oid().value.to_string();

        bsoncxx::types::b_date dt = result->view()["last-access"].get_date();
        User *u = new User(id, name, surname, email, password, dt);
        return u;

    }

    return nullptr;
}

void Mongodb::UpdateUserLastAccess(const string &id) {
    auto now = std::chrono::system_clock::now();
    bsoncxx::types::b_date dt{now};
    auto client = pool->acquire();
    this->coll = client->database("testdb")["users"];
    //coll = this->db["users"];       //UPDATE users SET last-access = now WHERE id = id
    coll.update_one(document{} << "_id" << bsoncxx::oid{stdx::string_view{id}} << finalize,
                    document{} << "$set" << open_document <<
                               "last-access" << dt << close_document << finalize);
}

bsoncxx::types::b_date Mongodb::getLastAccess(const string &userid) {
    auto client = pool->acquire();
    this->coll = client->database("testdb")["users"];
    //coll = this->db["users"];
    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "_id" << bsoncxx::oid{stdx::string_view{userid}} << finalize);
    if (result) {
        return result->view()["last-access"].get_date();
    }

    bsoncxx::types::b_date dt{std::chrono::system_clock::now()};
    return dt;
}


//==========================Chat=========================//
string Mongodb::CreateChat(Chat *ch) {

    //creare la chat se esiste ricaricarla
    Chat *ch1 = getChat(ch);
    if (ch1 != nullptr) {
        delete ch1;
        return "Chat already exist.";
    }
    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //this->coll = db["chats"];
    auto builder = bsoncxx::builder::stream::document{};

    bool isgroup = false;
    if (ch->Participants.size() > 2) {
        isgroup = true;
    }
    auto array_builder = bsoncxx::builder::basic::array{};

    for (const auto &element : ch->Participants) {
        array_builder.append(element);
    }
    bsoncxx::document::value doc_chat = builder

            << "name" << ch->Name
            << "partecipants" << array_builder
            << "isgroup" << isgroup
            << "messages" << open_array << close_array

            << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_chat.view();
    coll.insert_one(view);
    cout << "Chat inserita \n";
    //Deve tornare True;
    return "ok";

}

Chat *Mongodb::getChatById(const string &chatId) {

    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];

    //chat ha: id_chat(generato dal db) - Nomechat - lista partecipanti - isGroup - message[]

    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "_id" << bsoncxx::oid{stdx::string_view{chatId}} << finalize);

    if (result) {
        string id = result->view()["_id"].get_oid().value.to_string();

        Chat *chat = new Chat(id);


        for (const auto &element : result->view()["partecipants"].get_array().value) { //for each
            string partecipant_id = element.get_utf8().value.to_string();
            chat->addPartecipant(partecipant_id);
        }

        string name = result->view()["name"].get_utf8().value.to_string();
        chat->Name = name;

        bool isGroup = result->view()["isgroup"].get_bool().value;
        chat->IsGroup = isGroup;

        for (const auto &element : result->view()["messages"].get_array().value) {
            string content = element["content"].get_utf8().value.to_string();
            string senderName = element["senderName"].get_utf8().value.to_string();
            string sender_id = element["sender_id"].get_utf8().value.to_string();
            string media_id = element["media"].get_utf8().value.to_string();
            bsoncxx::types::b_date date = element["receptionDate"].get_date();
            Message *msg = new Message(content, sender_id, senderName, media_id, date);
            chat->addMessage(msg);
        }

        return chat;
    }

    return nullptr;
}

Chat *Mongodb::getChat(Chat *c) {
    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];

    auto array_builder = bsoncxx::builder::stream::array{};

    for (const auto &element : c->Participants) { //for each
        array_builder << element;
    }

    bool checkIsgroup = false;

    if (c->Participants.size() > 2) {
        checkIsgroup = true;
    }


    //db.chats.find_one( {   partecipants : { $all : [ 1, 2] } , isGroup: false   } )
    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "partecipants" << open_document << "$all"
                       << array_builder << close_document << "isgroup" << checkIsgroup << finalize);


    if (result) {
        string id = result->view()["_id"].get_oid().value.to_string();

        Chat *chat = new Chat(id);

        for (const auto &element : result->view()["partecipants"].get_array().value) { //for each
            string partecipant_id = element.get_utf8().value.to_string();
            chat->addPartecipant(partecipant_id);
        }


        string name = result->view()["name"].get_utf8().value.to_string();
        chat->Name = name;

        bool isGroup = result->view()["isgroup"].get_bool().value;
        chat->IsGroup = isGroup;

        for (const auto &element : result->view()["messages"].get_array().value) { //for each
            string content = element["content"].get_utf8().value.to_string();
            string senderName = element["senderName"].get_utf8().value.to_string();
            string sender_id = element["sender_id"].get_utf8().value.to_string();
            string media_id = element["media"].get_utf8().value.to_string();
            bsoncxx::types::b_date date = element["receptionDate"].get_date();
            Message *msg = new Message(content, sender_id, senderName, media_id, date);
            chat->addMessage(msg);
        }

        return chat;
    }

    return nullptr;
}

Chat *Mongodb::updateMessage(const string &chatId, Message *m) {

    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];

    auto result = coll.update_one(document{} << "_id" << bsoncxx::oid{stdx::string_view{chatId}} << finalize,
                                  document{} << "$push" << open_document << "messages" <<
                                             open_document << "content" << m->Content <<
                                             "senderName" << m->SenderName <<
                                             "sender_id" << m->Sender_id <<
                                             "media" << m->Media <<
                                             "receptionDate" << m->ReceptionDate << close_document
                                             << close_document << finalize);

    return getChatById(chatId);
}

vector<Chat *> Mongodb::getChats(const string &userid) {

    vector<Chat*> ch;
    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];

    mongocxx::cursor cursor = coll.find(
            document{} << "partecipants" << userid << finalize);

    for (auto result : cursor) {
        string id = result["_id"].get_oid().value.to_string();

        Chat *chat = new Chat(id);

        for (const auto &element : result["partecipants"].get_array().value) { //for each
            string partecipant_id = element.get_utf8().value.to_string();
            chat->addPartecipant(partecipant_id);
        }


        string name = result["name"].get_utf8().value.to_string();
        chat->Name = name;

        bool isGroup = result["isgroup"].get_bool().value;
        chat->IsGroup = isGroup;

        for (const auto &element : result["messages"].get_array().value) { //for each
            string content = element["content"].get_utf8().value.to_string();
            string senderName = element["senderName"].get_utf8().value.to_string();
            string sender_id = element["sender_id"].get_utf8().value.to_string();
            string media_id = element["media"].get_utf8().value.to_string();
            bsoncxx::types::b_date date = element["receptionDate"].get_date();
            Message *msg = new Message(content, sender_id, senderName, media_id, date);
            chat->addMessage(msg);
        }

        ch.push_back(chat);
    }

    return ch;
}

string Mongodb::deleteChatById(const string &chatid){

    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];


    auto result =coll.delete_one(
            document{} << "_id" << bsoncxx::oid{stdx::string_view{chatid}} << finalize);

    if(result->deleted_count()==1){
        return "ok";
    }else{
        return "Chat doesn't exist.";
    }
}

string Mongodb::deletePartecipant(const string& chatid, const string& userid){
    auto client = pool->acquire();
    this->coll = client->database("testdb")["chats"];
    //coll = this->db["chats"];

    auto result = coll.update_one(document{} << "_id" << bsoncxx::oid{stdx::string_view{chatid}} << finalize,
                                  document{} << "$pull" << open_document << "partecipants" << userid
                                             << close_document << finalize);


    if(result->modified_count()==1){
        return "ok";
    }else{
        return "Can't remove this user from the chat.";
    }
}
