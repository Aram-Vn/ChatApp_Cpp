#include "../headers/ChatServer.h"

#include <iostream>
#include <sstream>

std::vector<ChatClient>::iterator ChatServer::GetClient(const my::ServerClient& client) noexcept
{
    return std::find_if(m_Clients.begin(), m_Clients.end(), [&client](auto& elem) { return *elem.client == client; });
}

void ChatServer::Event_OnInit()
{
    std::cout << "[!]: Waiting for a connection..." << std::endl;
}

void ChatServer::Event_OnClientConnect(const my::ServerClient& client)
{
    m_Clients.emplace_back(ChatClient{ .name = std::nullopt, .client = &client });

    std::cout << "[!]: ServerClient connected from: '" << client.GetIPv4() << ":" << client.GetPort() << "'."
              << std::endl;
}

void ChatServer::Event_OnClientDisconnect(const my::ServerClient& client)
{
    auto it = GetClient(client);

    if (it->name)
    {
        std::cout << "[!]: " << *it->name << " (" << client.GetIPv4() << ":" << client.GetPort() << ") disconnected."
                  << std::endl;
    }
    else
    {
        std::cout << "[!]: " << client.GetIPv4() << ":" << client.GetPort() << " disconnected." << std::endl;
    }

    m_Clients.erase(it);
}

void ChatServer::Event_OnReceive(const my::ServerClient& client, const my::DataPacket& packet)
{
    auto it = GetClient(client);

    if (it->name)
    {
        std::stringstream ss;
        ss << "[" << *it->name << "]: " << std::string{ reinterpret_cast<const char*>(packet.buffer), packet.len }
           << std::endl;

        std::string str = ss.str();
        std::cout << str << std::endl;

        auto send_packet =
            my::DataPacket{ .buffer = reinterpret_cast<std::uint8_t*>(str.data()), .len = str.size() + 1 };

        for (const auto& elem : GetConnectedClients())
        {
            if (elem != client)
            {
                this->Send(elem, send_packet);
            }
        }
    }
    else
    {
        it->name = std::string{ (const char*)packet.buffer, packet.len };
    }
}
