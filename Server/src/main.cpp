#include <iostream>

#include "Server.h"

class ChatServer : public my::Server
{
private:
    void Event_OnInit() override
    {
        std::cout << "[!]: Waiting for a connection..." << std::endl;
    }

    void Event_OnClientConnect(const my::Client& client) override
    {
        std::cout << "[!]: Client connected from: '" << client.GetIPv4() << ":" << client.GetPort() << "' as "
                  << client.GetNick() << std::endl;
    }

    void Event_OnClientDisconnect(const my::Client& client) override
    {
        std::cout << "[!]: " << client.GetNick() << " (" << client.GetIPv4() << ":" << client.GetPort()
                  << ") disconnected." << std::endl;
    }
    
    void Event_OnReceive(const my::Client& client, const my::DataPacket& packet) override
    {
        std::cout << "[" << client.GetNick() << client.GetPort()
                  << "]: " << std::string{ (const char*)packet.buffer, packet.len } << std::endl;
    }
};

int main(const int argc, const char* argv[])
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    ChatServer server;
    server.Init(7777);
    
    while (server.IsRunning())
    {
        server.Update();
    }

    enet_deinitialize();
    return 0;
}