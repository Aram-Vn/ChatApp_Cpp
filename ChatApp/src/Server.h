#pragma once

#include "Client.h"
#include "Common.h"

namespace my {
    class Server
    {
    public:
        static constexpr auto MAX_CLIENT_COUNT  = 16;
        static constexpr auto MAX_CHANNEL_COUNT = 1;
        static constexpr auto DEFAULT_TIMEOUT   = 5000;

    private:
        ENetHost*           m_Host = nullptr;
        ENetAddress         m_EndPoint;
        ENetEvent           m_Event;
        std::vector<Client> m_ConnectedClients;

    private:
        static Server* s_Instance;

    public:
        static Server& Get() noexcept;
        static void    Dispose() noexcept;

    public:
        constexpr Server() noexcept {};
        ~Server() noexcept;

    public:
        void Init(const std::uint16_t port) noexcept;
        void Run() noexcept;

    private:
        void Event_OnClientConnect() noexcept;
        void Event_OnClientDisconnect() noexcept;
        void Event_OnReceive() noexcept;
    };
} // namespace my