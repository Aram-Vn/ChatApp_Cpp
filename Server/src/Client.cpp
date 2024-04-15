#include "Client.h"

namespace my {
    Client::Client(ENetPeer* peer, const std::string_view name) noexcept
        : m_Address(peer->address),
          m_Peer(peer),
          m_Nick(name)
    {
    }
} // namespace my