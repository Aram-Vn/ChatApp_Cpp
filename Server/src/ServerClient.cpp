#include "../headers/ServerClient.h"
#include <cstddef>

namespace my {
    ServerClient::ServerClient(ENetPeer* peer) noexcept
        : m_Address(peer->address),
          m_Peer(peer)
    {
    }

    std::string ServerClient::GetIPv4() const noexcept
    {
        const std::size_t       size   = 128;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
        enet_address_get_host_ip(&m_Address, buffer.get(), size);
        return std::string(buffer.get());
    }

    ENetPeer* ServerClient::GetPeer() noexcept
    {
        return m_Peer;
    }

    ENetPeer* ServerClient::GetPeer() const noexcept
    {
        return m_Peer;
    }

    std::uint16_t ServerClient::GetPort() const noexcept
    {
        return m_Address.port;
    }

    ServerClient::operator ENetAddress() const
    {
        return m_Address;
    }

    bool operator==(const ServerClient& lhv, const ServerClient& rhv) noexcept
    {
        return lhv.m_Address.host == rhv.m_Address.host && lhv.m_Address.port == rhv.m_Address.port;
    }
} // namespace my
