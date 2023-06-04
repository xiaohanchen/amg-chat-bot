//
// Created by Haiying on 17/05/2023.
//

#include <iostream>

#ifndef AMG_CHAT_BOT_CONSTANTS_H
#define AMG_CHAT_BOT_CONSTANTS_H

//number of workers thraeds
#define NUMBER_OF_WORKERS 10

//max number of clients per worker
#define MAX_CLIENT_NUM_PER_WORKER 10

//select, epoll, kqueue
#define COMMUNICATION_TYPE SELECT

// number of clients to be created
#define NUMBER_OF_CLIENTS 50

//interval in sec between group of clients sending message
#define CLIENT_MSG_SEND_INTERVAL 2

const std::string SERVER_HOST = "127.0.0.1";
const int SERVER_PORT = 65102;
const int MAX_CHAR_TO_READ = 256;


enum BufferCheckEnum {
    FAILURE,
    TIMEOUT,
    SUCCESS
};

#endif //AMG_CHAT_BOT_CONSTANTS_H




