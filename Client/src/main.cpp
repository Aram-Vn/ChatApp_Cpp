#include <iostream>

#include "Client.h"

class ChatClient : public my::Client
{
protected:
    void Event_OnConnect() override
    {
        std::cout << "[!]: Connected to the server." << std::endl;
    }
    void Event_OnDisconnect() override
    {
        std::cout << "[!]: Disconnected from the server." << std::endl;
    }
    void Event_OnReceive(const my::DataPacket& data) override
    {
        std::cout << "[!]: Server: " << std::string((char*)data.buffer, data.len) << std::endl;
    }
};

int main(const int argc, const char* argv[])
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    std::string   ip;
    std::uint16_t port;

    std::cout << "IP: ";
    std::getline(std::cin, ip);
    std::cout << "Port";
    std::cin >> port;

    ChatClient client;
    if (client.Connect(ip, port, 5000))
    {
        std::thread(
            [&client]
            {
                while (client.IsConnected())
                {
                    std::string str;
                    std::getline(std::cin, str);
                    client.Send(my::DataPacket{ .buffer = (std::uint8_t*)str.data(), .len = str.size() });
                }
            })
            .detach();

        while (client.IsConnected())
            client.Update();
    }
    else
        std::cerr << "Failed to connect to the server." << std::endl;

    enet_deinitialize();
    return 0;
}
