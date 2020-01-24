//
// Created by chryc on 23/12/2019.
//

#include "MediaManager.h"
#include <fstream>
#include <iostream>
#include <random>

string random_string() {
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str
}

string MediaManager::saveMedia(const string &media) {

    string id = random_string();
    cout << id << "\n";

    string t(id);
    ofstream f;
    f.open("./MediaFiles/" + t + ".txt");
    f << media;
    f.close();
    return t;
}

string MediaManager::getMediaById(const string &id) {

    string base64("");
    ifstream f("./MediaFiles/" + id + ".txt");
    if (f.is_open()) {
        getline(f, base64);
        f.close();
        return base64;
    }
    cout << "Media " << id << " not found!\n";
    return base64;
}

