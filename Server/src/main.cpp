#include <iostream>

#include "Server.h"

int main(const int argc, const char* argv[])
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    enet_deinitialize();
    return 0;
}