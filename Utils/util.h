//
// Created by chryc on 29/12/2019.
//

#include <iostream>
#include <chrono>
#include <string>

#ifndef CHAT_SERVER_UTIL_H
#define CHAT_SERVER_UTIL_H

#endif //CHAT_SERVER_UTIL_H

using namespace std;

string formatDateFromMilliseconds(unsigned long long milliseconds) {
    time_t a = milliseconds / 1000; // or 1439467747
    struct tm *timeinfo = localtime(&a);

    char buffer[256];

    strftime(buffer, sizeof(buffer), "%A %d at %H:%M", timeinfo);
    string time(buffer);
    return "Last access " + time;
}