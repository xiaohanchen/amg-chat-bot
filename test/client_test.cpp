//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include "../include/chat_client.h"
#include "../include/constants.h"

int main(){
    ChatClient chatClient;

    chatClient.connectToServer(SERVER_PORT, LOCALHOST);

    std::cout << "Server started" << std::endl;
    return 0;
}

//#endif