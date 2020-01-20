//
// Created by chryc on 23/12/2019.
//

#ifndef CHAT_SERVER_MEDIAMANAGER_H
#define CHAT_SERVER_MEDIAMANAGER_H

#include <string>

#define FOLDER "MediaFiles"
using namespace std;

class MediaManager {

public:
    /* MediaManager(){
         CreateFolder(FOLDER);
     }; */

    /* void CreateFolder(const char *path)
     {
         if(!CreateDirectory(path ,NULL))
         {
             return;
         }
     };*/

    static string saveMedia(const string &media); //return media's id

    static string getMediaById(const string &id); //return base64 media

};


#endif //CHAT_SERVER_MEDIAMANAGER_H
