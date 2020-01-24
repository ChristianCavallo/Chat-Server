//
// Created by chryc on 23/12/2019.
//

#ifndef CHAT_SERVER_MEDIAMANAGER_H
#define CHAT_SERVER_MEDIAMANAGER_H

#include <string>

using namespace std;

namespace MediaManager {

    string saveMedia(const string &media); //return media's id

    string getMediaById(const string &id); //return base64 media

};


#endif //CHAT_SERVER_MEDIAMANAGER_H
