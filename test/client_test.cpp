//
// Created by Haiying on 17/05/2023.
//

//#ifdef SERVER_TEST

#include <iostream>
#include <unistd.h>
#include "../include/chat_client.h"
#include "../include/constants.h"

int main(){
    ChatClient chatClient1;
    ChatClient chatClient2;
    ChatClient chatClient3;

    chatClient1.connectToServer(LOCALHOST, SERVER_PORT);
    chatClient2.connectToServer(LOCALHOST, SERVER_PORT);
    chatClient3.connectToServer(LOCALHOST, SERVER_PORT);


    int i = 0;
    while (true){
        chatClient1.sendMsg("1hello world " + std::to_string(i++));
        chatClient2.sendMsg("2hello world " + std::to_string(i++));
        chatClient3.sendMsg("3hello world " + std::to_string(i++));
        sleep(1);
    }
    return 0;
}

//#endif