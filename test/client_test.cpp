//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include "../include/chat_client.h"
#include "../include/constants.h"

int main(){
    ChatClient chatClient;

    chatClient.connectToServer(LOCALHOST, SERVER_PORT);

    chatClient.sendMsg("hello world");

    return 0;
}

//#endif