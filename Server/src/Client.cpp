#include "../headers/Client.h"

namespace my {
    Client::Client(ENetPeer* peer) noexcept
        : m_Address(peer->address),
          m_Peer(peer)
    {
    }

    std::string Client::GetIPv4() const noexcept
    {
        const auto              size   = 128;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
        enet_address_get_host_ip(&m_Address, buffer.get(), size);
        return std::string(buffer.get());
    }

    ENetPeer* Client::GetPeer() noexcept
    {
        return m_Peer;
    }

    ENetPeer* Client::GetPeer() const noexcept
    {
        return m_Peer;
    }

    std::uint16_t Client::GetPort() const noexcept
    {
        return m_Address.port;
    }

    Client::operator ENetAddress() const
    {
        return m_Address;
    }

    bool operator==(const Client& lhv, const Client& rhv) noexcept
    {
        return lhv.m_Address.host == rhv.m_Address.host && lhv.m_Address.port == rhv.m_Address.port;
    }
} // namespace my
