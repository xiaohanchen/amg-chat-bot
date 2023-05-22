//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include <unistd.h>
#include "../include/chat_client.h"
#include "../include/constants.h"

int main(){
    ChatClient chatClient;

    chatClient.connectToServer(LOCALHOST, SERVER_PORT);


    int i = 0;
    while (true){
        chatClient.sendMsg("hello world " + std::to_string(i++));
        sleep(2);
    }
    return 0;
}

//#endif