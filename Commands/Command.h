//
// Created by chryc on 07/12/2019.
//

#include <string>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#ifndef CHAT_SERVER_COMMAND_H
#define CHAT_SERVER_COMMAND_H

#endif //CHAT_SERVER_COMMAND_H

using namespace std;
using namespace rapidjson;

class Command {
public:
    int id;

    Command(int id) {
        this->id = id;
    }


protected:
    template<typename Writer>
    void Serialize(Writer &writer) const {
        writer.String("id");
        writer.Uint(id);
    };

};

class CommandKey : public Command {
private:
    string key;
public:
    CommandKey(int id, const string &key) : Command(id), key(key) {}

    template<typename Writer>
    void Serialize(Writer &writer) const {
        writer.StartObject();
        Command::Serialize(writer);
        writer.String("key");
        writer.String(key.c_str(), static_cast<SizeType>(key.size()));
        writer.EndObject();
    }

    virtual string getSerializedString() {
        StringBuffer sb;
        PrettyWriter<StringBuffer> prettyWriter(sb);
        this->Serialize(prettyWriter);
        return sb.GetString();
    }

};
