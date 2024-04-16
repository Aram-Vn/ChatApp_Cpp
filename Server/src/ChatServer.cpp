#include "../headers/ChatServer.h"

#include <iostream>
#include <sstream>

void ChatServer::Event_OnInit()
{
    std::cout << "[!]: Waiting for a connection..." << std::endl;
}

void ChatServer::Event_OnClientConnect(const my::Client& client)
{
    std::cout << "[!]: Client connected from: '" << client.GetIPv4() << ":" << client.GetPort() << "' as "
              << client.GetNick() << std::endl;
}

void ChatServer::Event_OnClientDisconnect(const my::Client& client)
{
    std::cout << "[!]: " << client.GetNick() << " (" << client.GetIPv4() << ":" << client.GetPort() << ") disconnected."
              << std::endl;
}

void ChatServer::Event_OnReceive(const my::Client& client, const my::DataPacket& packet)
{
    std::stringstream ss;
    ss << "[" << client.GetNick() << client.GetPort() << "]: " << std::string{ (const char*)packet.buffer, packet.len }
       << std::endl;

    std::string str = ss.str();
    std::cout << str << std::endl;

    auto send_packet = my::DataPacket{ .buffer = (std::uint8_t*)str.c_str(), .len = str.size() + 1 };

    for (const auto& e : GetConnectedClients())
    {
        if (e != client)
        {
            this->Send(e, send_packet);
        }
    }
}