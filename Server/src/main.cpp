#include <iostream>

#include "../headers/ChatServer.h"

int main(const int argc, const char* argv[])
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet.\n";
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