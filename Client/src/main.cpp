#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include "../headers/ChatClient.h"

#include <atomic>

std::atomic<bool> disconnect = false;

void signal_handler(int signal_num)
{
    std::cout << "\npress enter" << std::endl;
    disconnect = true;
}

int main()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet." << std::endl;
        return EXIT_FAILURE;
    }

    std::string   ip   = "127.0.0.1";
    std::string   nick = "no";
    std::uint16_t port = 7777;
    std::thread   chat_thread;

    std::cout << "Nick: ";
    std::getline(std::cin, nick);
    std::cout << std::endl;

    ChatClient client{ nick };

    std::signal(SIGINT, signal_handler);

    std::cout << "\nHI : " << nick << std::endl;
    std::cout << "You can disconnect using: /exit or Ctrl+D" << std::endl;
    std::cout << "Have a good day\n" << std::endl;

    if (client.Connect(ip, port, 5000))
    {
        chat_thread = std::thread(
            [&client]
            {
                while (client.IsConnected())
                {
                    if (disconnect)
                    {
                        client.Disconnect();
                        exit(2);
                    }

                    std::cout << ">>> ";
                    std::string str;
                    std::getline(std::cin, str);

                    if (str.starts_with("/exit") || feof(stdin))
                    {
                        client.Disconnect();
                    }
                    else
                    {
                        client.SendString(str);
                    }
                }
            });

        while (client.IsConnected())
        {
            client.Update();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    else
    {
        std::cerr << "[!]: Failed to connect to the server." << std::endl;
    }

    if (chat_thread.joinable())
    {
        chat_thread.join();
    }
    enet_deinitialize();
    return 0;
}
