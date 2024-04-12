#include "Client.h"

namespace my {
    Client::Client(ENetPeer* peer) noexcept
        : m_Address(peer->address),
          m_Peer(peer)
    {
    }
} // namespace my