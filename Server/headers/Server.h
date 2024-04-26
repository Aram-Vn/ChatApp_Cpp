#ifndef CHATAPP_CPP_SERVER_HEADERS_SERVER_H
#define CHATAPP_CPP_SERVER_HEADERS_SERVER_H

#include <Common.h>
#include <Packet.h>

#include "ServerClient.h"

    namespace Network {

    namespace Defaults {

        constexpr std::uint32_t TIMEOUT             = 5000;
        constexpr std::uint8_t  CHANNEL_ID          = 0;
        constexpr std::uint32_t INCOMING_BAND_WIDTH = 0; // unlimited bandwidth
        constexpr std::uint32_t OUTGOING_BAND_WIDTH = 0; // unlimited bandwidth

    } // namespace Defaults

    namespace Max {

        constexpr std::size_t CLIENT_COUNT  = 16;
        constexpr std::size_t CHANNEL_COUNT = 1;

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

#endif // CHATAPP_CPP_SERVER_HEADERS_SERVER_H