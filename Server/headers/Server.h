#pragma once

#include <Common.h>
#include <Packet.h>

#include "ServerClient.h"

namespace Network {

    namespace Defaults {

        constexpr int TIMEOUT    = 5000;
        constexpr int CHANNEL_ID = 0;

    } // namespace Defaults

    namespace Max {

        constexpr int CLIENT_COUNT  = 16;
        constexpr int CHANNEL_COUNT = 1;

    } // namespace  Max

} // namespace Network

namespace my {
    class Server
    {
    public:
        Server() noexcept {};
        virtual ~Server() noexcept;

    public:
        bool Init(const std::uint16_t port) noexcept;
        bool IsRunning() const noexcept;
        void Update();

    protected:
        bool                           Send(const ServerClient& client, DataPacket& packet);
        const std::list<ServerClient>& GetConnectedClients() const noexcept;

    protected:
        virtual void Event_OnInit()                                                        = 0;
        virtual void Event_OnClientConnect(const ServerClient& client)                     = 0;
        virtual void Event_OnClientDisconnect(const ServerClient& client)                  = 0;
        virtual void Event_OnReceive(const ServerClient& client, const DataPacket& packet) = 0;

    private:
        ENetHost*               m_Host = nullptr;
        ENetAddress             m_EndPoint;
        ENetEvent               m_Event;
        std::list<ServerClient> m_ConnectedClients;
        bool                    m_Running = false;
    };
} // namespace my
