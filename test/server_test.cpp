//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include <thread>
#include <csignal>
#include "../include/chat_server.h"
#include "../include/constants.h"
ChatServer chatServer;

void processExit(int i){
    std::cout << "process exit..." <<std::endl;
    chatServer.close();
    exit(0);

}

int main(){
    signal(SIGINT, processExit);
    signal(SIGTERM, processExit);
    signal(SIGHUP, processExit);

    chatServer.start(SERVER_PORT,2,  NUMBER_OF_WORKERS);
    std::cout << "Server started" << std::endl;

    while (true){

    }
    return 0;
}

//#endif