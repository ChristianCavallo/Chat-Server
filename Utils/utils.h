//
// Created by Noemi on 02/01/2020.
//

#ifndef CHAT_SERVER_UTILS_H
#define CHAT_SERVER_UTILS_H

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

namespace utils {
    static string formatDateFromMilliseconds(unsigned long long milliseconds) {
        time_t a = milliseconds / 1000; // or 1439467747
        struct tm *timeinfo = localtime(&a);

        char buffer[256];

        strftime(buffer, sizeof(buffer), "%A %d at %H:%M", timeinfo);
        string time(buffer);
        return time;
    }
}



#endif //CHAT_SERVER_UTILS_H
