#pragma once

#include "Common.h"
#include "enet/enet.h"
#include <memory>

namespace my {
    class Client
    {
    private:
        ENetAddress m_Address;
        ENetPeer*   m_Peer = nullptr;
        std::string m_Nick;

    public:
        Client(ENetPeer* peer, const std::string_view name) noexcept;

    public:
        inline const std::string_view GetNick() const noexcept
        {
            return m_Nick;
        }
        inline std::string GetIPv4() const noexcept
        {
            const auto              size   = 128;
            std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
            enet_address_get_host_ip(&m_Address, buffer.get(), size);
            std::string str(buffer.get());
            return str;
        }

        inline std::uint16_t GetPort() const noexcept
        {
            return m_Address.port;
        }

    public:
        explicit operator ENetAddress()
        {
            return m_Address;
        }
    };
} // namespace my