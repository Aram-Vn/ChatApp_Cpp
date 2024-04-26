#ifndef CHATAPP_CPP_SERVER_HEADERS_SERVER_H
#define CHATAPP_CPP_SERVER_HEADERS_SERVER_H

#include "ServerClient.h"
#include <Common.h>
#include <Packet.h>
#include <boost/functional/hash.hpp>
#include <functional>
#include <unordered_map>

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

template <>
struct std::hash<ENetAddress>
{
    std::size_t operator()(const ENetAddress& s) const noexcept
    {
        std::size_t h1 = std::hash<std::uint32_t>{}(s.host);
        std::size_t h2 = std::hash<std::uint16_t>{}(s.port);
        std::size_t seed = 0;
        boost::hash_combine(seed, h1);
        boost::hash_combine(seed, h2);
        return seed;
    }
};

bool operator==(const ENetAddress& lhv, const ENetAddress& rhv) noexcept;

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
        bool                                                 Send(const ServerClient& client, DataPacket& packet);
        const std::unordered_map<ENetAddress, ServerClient>& GetConnectedClients() const noexcept;

    protected:
        virtual void Event_OnInit()                                                        = 0;
        virtual void Event_OnClientConnect(const ServerClient& client)                     = 0;
        virtual void Event_OnClientDisconnect(const ServerClient& client)                  = 0;
        virtual void Event_OnReceive(const ServerClient& client, const DataPacket& packet) = 0;

    private:
        ENetHost*                                     m_Host = nullptr;
        ENetAddress                                   m_EndPoint;
        ENetEvent                                     m_Event;
        std::unordered_map<ENetAddress, ServerClient> m_ConnectedClients;
        bool                                          m_Running = false;
    };
} // namespace my

#endif // CHATAPP_CPP_SERVER_HEADERS_SERVER_H