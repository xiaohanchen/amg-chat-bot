//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include "../include/chat_server.h"
#include "../include/constants.h"

int main(){
    ChatServer chatServer;

    chatServer.start(CLIENT_PORT);
    std::cout << "Server started" << std::endl;
    return 0;
}

//#endif