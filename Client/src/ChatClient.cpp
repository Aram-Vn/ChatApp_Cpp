#include "../headers/ChatClient.h"
#include <iostream>
#include <string>

ChatClient::ChatClient() 
{
}

ChatClient::ChatClient(const std::string_view nick)
    : m_Nick(nick)
{
}

const std::string& ChatClient::Get_Nick() const 
{
    return m_Nick;
}

bool ChatClient::SendString(const std::string_view string) const noexcept
{
    my::DataPacket packet{ .buffer = (std::uint8_t*)string.data(), .len = string.size() };
    return this->Send(packet);
}

void ChatClient::Event_OnConnect()
{
    std::cout << "[!]: Connected to the server." << std::endl;
    this->SendString(m_Nick);
}

void ChatClient::Event_OnDisconnect()
{
    std::cout << "[!]: Disconnected from the server." << std::endl;
}

void ChatClient::Event_OnReceive(const my::DataPacket& data)
{
    std::cout << std::endl << std::string((char*)data.buffer, data.len) << std::endl;
}
