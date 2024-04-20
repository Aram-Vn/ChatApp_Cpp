#include "../headers/ChatClient.h"
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include <atomic>

namespace Network {
    enum class ConnectionState
    {
        Connected,
        Disconnected
    }; // enum class ConnectionState

    std::atomic<ConnectionState> connection_state = ConnectionState::Connected;
} // namespace Network

void signal_handler(int signal_num)
{
    std::cout << "\nPlese press enter" << std::endl;
    Network::connection_state = Network::ConnectionState::Disconnected;
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

    std::cout << "IP: ";
    std::getline(std::cin, ip);

    std::cout << "Port: ";
    std::cin >> port;
    std::cin.get();

    std::cout << "Nick: ";
    std::getline(std::cin, nick);
    std::cout << std::endl;

    ChatClient client{ nick };

    std::signal(SIGINT, signal_handler);

    std::cout << "\nHI: " << nick << std::endl;
    std::cout << "You can disconnect using: /exit or Ctrl+D" << std::endl;
    std::cout << "You can see your current nick by typing /nick" << std::endl;
    std::cout << "To clear the screen, use /cl" << std::endl;
    std::cout << "Have a good day!!!" << std::endl;

    if (client.Connect(ip, port, 5000))
    {
        chat_thread = std::thread(
            [&client]
            {
                while (client.IsConnected())
                {
                    if (Network::connection_state == Network::ConnectionState::Disconnected)
                    {
                        client.Disconnect();
                        exit(SIGINT);
                    }
                    else
                    {
                        std::cout << ">>> ";
                        std::string str;
                        std::getline(std::cin, str);

                        if (str.empty())
                        {
                            continue;
                        }

                        if (str.starts_with("/exit") || feof(stdin))
                        {
                            client.Disconnect();
                            break;
                        }
                        else
                        {
                            switch (str[0])
                            {
                                case '/':
                                    if (str.starts_with("/nick"))
                                    {
                                        std::cout << "Your current nick is: ";
                                        std::cout << client.Get_Nick() << std::endl;
                                    }
                                    else if (str.starts_with("/cl"))
                                    {
                                        system("clear");
                                    }
                                    break;
                                default: client.SendString(str); break;
                            }
                        }
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