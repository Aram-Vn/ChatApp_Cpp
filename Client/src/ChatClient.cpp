#include "../headers/ChatClient.h"
#include <iostream>
#include <string>

ChatClient::ChatClient() {}

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
    // const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(string.data());
    // my::DataPacket packet{ .buffer = data, .len = string.size() };

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
    const char* buffer = reinterpret_cast<const char*>(data.buffer);
    std::cout << std::endl << std::string(buffer, data.len) << std::endl;
}

void ChatClient::Greeting() const noexcept 
{
    std::cout << "\nHI: " << m_Nick << std::endl;
    std::cout << "You can disconnect using: /exit or Ctrl+D" << std::endl;
    std::cout << "You can see your current nick by typing /nick" << std::endl;
    std::cout << "To clear the screen, use /cl" << std::endl;
    std::cout << "Have a good day!!!" << std::endl;
}