//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include <thread>
#include "../include/chat_server.h"
#include "../include/constants.h"

int main(){
    ChatServer chatServer;

    chatServer.start(SERVER_PORT,3);
    std::cout << "Server started" << std::endl;

    new std::thread(&ChatServer::acceptClient, chatServer);

    while (true){

    }
    return 0;
}

//#endif