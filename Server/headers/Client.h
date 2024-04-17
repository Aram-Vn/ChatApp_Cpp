#pragma once

#include "enet/enet.h"
#include <Common.h>
#include <memory>

namespace my {
    class Client
    {
    public: // ctors
        Client(ENetPeer* peer) noexcept;

    public: // operators
        explicit    operator ENetAddress() const;
        friend bool operator==(const Client& lhv, const Client& rhv) noexcept;

    public:                                     // geters
        std::string   GetIPv4() const noexcept; //
        ENetPeer*     GetPeer() noexcept;       //
        ENetPeer*     GetPeer() const noexcept; //
        std::uint16_t GetPort() const noexcept; //

    private:
        ENetAddress m_Address;
        ENetPeer*   m_Peer = nullptr;
    };
} // namespace my
