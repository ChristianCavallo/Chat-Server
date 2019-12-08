//
// Created by chryc on 07/12/2019.
//

#include <string>
#include "../include/rapidjson/prettywriter.h"
#include "../include/rapidjson/stringbuffer.h"
#ifndef CHAT_SERVER_COMMAND_H
#define CHAT_SERVER_COMMAND_H

#endif //CHAT_SERVER_COMMAND_H

using namespace std;
using namespace rapidjson;

class Command {
public:
    int id;
    string name;
    string other;
    Command(int id, string name, string other){
        this->id = id;
        this->name = name;
        this->other = other;
    }

    template <typename Writer>

    void Serialize(Writer& writer) const {
        writer.StartObject();

        writer.String("id");
        writer.Uint(id);

        writer.String("name");
        writer.String(name.c_str(), static_cast<SizeType>(name.length()));

        writer.String("other");
        writer.String(other.c_str(), static_cast<SizeType>(other.length()));

        writer.EndObject();
    }


};
