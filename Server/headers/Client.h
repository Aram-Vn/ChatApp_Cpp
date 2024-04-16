#pragma once

#include "enet/enet.h"
#include <Common.h>
#include <memory>

namespace my {
    class Client
    {
    public: // ctors
        Client(ENetPeer* peer, const std::string_view name) noexcept;

    public: // operators
        explicit    operator ENetAddress() const;
        friend bool operator==(const Client& lhv, const Client& rhv) noexcept;

    public: // geters
        const std::string_view GetNick() const noexcept;
        std::string            GetIPv4() const noexcept;
        ENetPeer*              GetPeer() noexcept;
        ENetPeer*              GetPeer() const noexcept;
        std::uint16_t          GetPort() const noexcept;

    public: // seters
        void SetNickname(std::string enteredNickname);

    private:
        ENetAddress m_Address;
        ENetPeer*   m_Peer = nullptr;
        std::string m_Nick;
    };
} // namespace my
