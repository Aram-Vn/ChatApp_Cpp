#include "../headers/ChatServer.h"

#include <iostream>
#include <sstream>

std::vector<ChatClient>::iterator ChatServer::GetClient(const my::Client& client) noexcept
{
    return std::find_if(m_Clients.begin(), m_Clients.end(), [&client](auto& e) { return *e.client == client; });
}

void ChatServer::Event_OnInit()
{
    std::cout << "[!]: Waiting for a connection..." << std::endl;
}

void ChatServer::Event_OnClientConnect(const my::Client& client)
{
    m_Clients.emplace_back(ChatClient{ .name = std::nullopt, .client = &client });

    std::cout << "[!]: Client connected from: '" << client.GetIPv4() << ":" << client.GetPort() << "'." << std::endl;
}

void ChatServer::Event_OnClientDisconnect(const my::Client& client)
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

void ChatServer::Event_OnReceive(const my::Client& client, const my::DataPacket& packet)
{
    auto it = GetClient(client);

    if (it->name)
    {
        std::stringstream ss;
        ss << "[" << *it->name << "]: " << std::string{ (const char*)packet.buffer, packet.len } << std::endl;

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
    else
    {
        it->name = std::string{ (const char*)packet.buffer, packet.len };
    }
}
