#include <iostream>
#include <string>

#include "../headers/ChatClient.h"
#include "Packet.h"



int main(const int argc, const char* argv[])
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet." << std::endl;
        return EXIT_FAILURE;
    }

    std::string   ip;
    std::string   nick;
    std::uint16_t port;

    std::cout << "IP: ";
    std::getline(std::cin, ip);
    
    std::cout << "Port: ";
    std::cin >> port;
    std::cin.get();

    // std::cout << "Nick: ";
    // std::getline(std::cin, nick);
    std::cout << std::endl;

    ChatClient client;
    
    if (client.Connect(ip, port, 5000))
    {
        std::thread(
            [&client]
            {
                while (client.IsConnected())
                {
                    std::cout << ">>> ";
                    std::string str;
                    std::getline(std::cin, str);
                    if (str.starts_with("/exit"))
                    {
                        client.Disconnect();
                    }
                    else
                    {
                        my::DataPacket packet{ .buffer = (std::uint8_t*)str.data(), .len = str.size() };
                        client.Send(packet);
                    }
                }
            })
            .detach();

        while (client.IsConnected())
        {
            client.Update();
        }
    }
    else
    {
        std::cerr << "[!]: Failed to connect to the server." << std::endl;
    }

    enet_deinitialize();
    return 0;
}
