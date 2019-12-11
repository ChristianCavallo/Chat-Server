//
// Created by chryc on 09/12/2019.
//

#ifndef CHAT_SERVER_BASE64_H
#define CHAT_SERVER_BASE64_H


#include <string>

std::string base64_encode(unsigned char const *, unsigned int len);

std::string base64_decode(std::string const &s);


#endif //CHAT_SERVER_BASE64_H
