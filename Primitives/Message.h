//
// Created by chryc on 29/12/2019.
//

#ifndef CHAT_SERVER_MESSAGE_H
#define CHAT_SERVER_MESSAGE_H

#include <string>
#include <bsoncxx/types.hpp>

using namespace std;

class Message {
private:

public:
    string Content;
    string Sender;
    string Media; // Id del cacher
    bsoncxx::types::b_date ReceptionDate{std::chrono::system_clock::now()};

    Message(const string &content, const string &sender, const string &media,
            const bsoncxx::types::b_date &receptionDate);

    Message(const string &content, const string &sender, const string &media);
};


#endif //CHAT_SERVER_MESSAGE_H
