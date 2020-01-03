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
    string Sender_id;
    string SenderName;
    string Media; // Id del cacher
    bsoncxx::types::b_date ReceptionDate{std::chrono::system_clock::now()};

    Message(const string &content, const string &sender_id, const string &senderName, const string &media,
            const bsoncxx::types::b_date &receptionDate);

    Message(const string &content, const string &sender_id, const string &senderName, const string &media);
};


#endif //CHAT_SERVER_MESSAGE_H
