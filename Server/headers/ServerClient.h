#ifndef CHATAPP_CPP_SERVER_HEADERS_SERVERCLIENT_H
#define CHATAPP_CPP_SERVER_HEADERS_SERVERCLIENT_H

#include "enet/enet.h"
#include <Common.h>
#include <memory>

namespace my {
    class ServerClient
    {
    public:
        explicit ServerClient(ENetPeer* peer) noexcept;

    public:
        explicit    operator ENetAddress() const;
        friend bool operator==(const ServerClient& lhv, const ServerClient& rhv) noexcept;

    public:
        std::string   GetIPv4() const noexcept;
        ENetPeer*     GetPeer() noexcept;
        ENetPeer*     GetPeer() const noexcept;
        std::uint16_t GetPort() const noexcept;

    private:
        ENetAddress m_Address;
        ENetPeer*   m_Peer = nullptr;
    };
} // namespace my

#endif // CHATAPP_CPP_SERVER_HEADERS_SERVERCLIENT_H