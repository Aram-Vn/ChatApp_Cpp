#include "../headers/ChatClient.h"
#include <iostream>
#include <string>

ChatClient::ChatClient() 
{
}

void ChatClient::Event_OnConnect()
{
    std::cout << "[!]: Connected to the server." << std::endl;
}

void ChatClient::Event_OnDisconnect()
{
    std::cout << "[!]: Disconnected from the server." << std::endl;
}

void ChatClient::Event_OnReceive(const my::DataPacket& data)
{
    std::cout << std::endl << std::string((char*)data.buffer, data.len) << std::endl;
}
