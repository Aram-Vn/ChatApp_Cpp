#pragma once

#include <Common.h>
#include <Packet.h>

#include "Client.h"

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
        void Init(const std::uint16_t port);
        void Run() noexcept;

    protected:
        virtual void Event_OnClientConnect()    = 0;
        virtual void Event_OnClientDisconnect() = 0;
        virtual void Event_OnReceive()          = 0;
    };
} // namespace my
