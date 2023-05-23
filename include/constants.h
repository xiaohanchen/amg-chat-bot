//
// Created by Haiying on 17/05/2023.
//

#include <iostream>

#ifndef AMG_CHAT_BOT_CONSTANTS_H
#define AMG_CHAT_BOT_CONSTANTS_H

#define MAX_CLIENT_NUM_PER_WORKER 10000

const std::string LOCALHOST = "127.0.0.1";
const int SERVER_PORT = 65102;
const int MAX_CHAR_TO_READ = 256;


enum BufferCheckEnum {
    FAILURE,
    TIMEOUT,
    SUCCESS
};

#endif //AMG_CHAT_BOT_CONSTANTS_H




