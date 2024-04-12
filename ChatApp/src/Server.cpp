#include "Server.h"
#include "enet/enet.h"
#include <stdexcept>

namespace my {
    Server* Server::s_Instance = nullptr;

    Server::~Server() noexcept
    {
        if (m_Host)
            enet_host_destroy(m_Host);
    }

    Server& Server::Get() noexcept
    {
        if (!s_Instance)
            s_Instance = new Server;
        return *s_Instance;
    }

    void Server::Dispose() noexcept
    {
        delete s_Instance;
        s_Instance = nullptr;
    }

    void Server::Init(const std::uint16_t port) noexcept
    {
        m_EndPoint.host = ENET_HOST_ANY;
        m_EndPoint.port = port;

        m_Host = enet_host_create(&m_EndPoint, Server::MAX_CLIENT_COUNT, Server::MAX_CHANNEL_COUNT, 0, 0);

        if (!m_Host)
            throw std::runtime_error("Failed to create server.");
    }

    void Server::Run() noexcept
    {
        while (enet_host_service(m_Host, &m_Event, Server::DEFAULT_TIMEOUT))
        {
            switch (m_Event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: Event_OnClientConnect(); break;
                case ENET_EVENT_TYPE_DISCONNECT: Event_OnClientDisconnect(); break;
                case ENET_EVENT_TYPE_RECEIVE: Event_OnReceive(); break;
                default: break;
            }
        }
    }

    void Server::Event_OnClientConnect() noexcept
    {
        Client client{ m_Event.peer };
        std::cout << "[!]: A client has connect from " << client.GetIPv4() << ":" << client.GetPort() << " as "
                  << client.GetNick() << std::endl;
    }
} // namespace my