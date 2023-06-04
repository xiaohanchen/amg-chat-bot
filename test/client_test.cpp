//
// Created by Haiying on 17/05/2023.
//


#include <iostream>
#include <unistd.h>
#include "../include/chat_client.h"
#include "../include/constants.h"

std::vector<ChatClient*> chatClientList;

void processExit(int i){
    std::cout << "process exit..." <<std::endl;
    for (const auto &item: chatClientList) {
        item->close();
        delete item;
    }

    exit(0);
}

int main(){
    //prevent connections from being open when process killed by ctrl+c and etc
    signal(SIGINT, processExit);
    signal(SIGTERM, processExit);
    signal(SIGHUP, processExit);

    for (int i = 0; i < NUMBER_OF_CLIENTS; ++i) {
        ChatClient* chatClient = new ChatClient();
        chatClient->connectToServer(SERVER_HOST, SERVER_PORT);
        chatClientList.push_back(chatClient);
    }


    int i = 0;
    while (true){
        for (const auto &item: chatClientList) {
            item -> sendMsg(item->getClientName() + ":hello world " + std::to_string(i++));
        }
        sleep(CLIENT_MSG_SEND_INTERVAL);
    }
    return 0;
}
