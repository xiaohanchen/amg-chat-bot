//
// Created by Haiying on 17/05/2023.
//

#include <iostream>

#ifndef AMG_CHAT_BOT_CONSTANTS_H
#define AMG_CHAT_BOT_CONSTANTS_H

const std::string LOCALHOST = "127.0.0.1";
const int SERVER_PORT = 65100;
const int CLIENT_PORT = 65200;
const int MAX_CHAR_TO_READ = 256;


enum BufferCheckEnum {
    FAILURE,
    TIMEOUT,
    SUCCESS
};

#endif //AMG_CHAT_BOT_CONSTANTS_H




