#include "../headers/Client.h"
#include "enet/enet.h"
#include <stdexcept>

namespace my {
    Client::Client()
    {
        m_ServerPeer.store(nullptr);

        m_Client = enet_host_create(nullptr, Network::Defaults::PEER_COUNT, Network::Defaults::PEER_CHANNEL_LIMIT,
                                    Network::Defaults::INCOMING_BAND_WIDTH, Network::Defaults::OUTGOING_BAND_WIDTH);

        if (!m_Client)
        {
            throw std::runtime_error("Clould not create client host.");
        }
    }

    Client::~Client() noexcept
    {
        if (m_Client)
        {
            Disconnect();
            enet_host_destroy(m_Client);
        }
    }

    bool Client::Connect(const std::string_view ip, const std::uint16_t port, const std::uint32_t timeout) noexcept
    {
        m_Ip                = ip;
        m_Port              = port;
        m_ConnectionTimeout = timeout;

        ENetAddress addr;
        addr.port = m_Port;

        if (enet_address_set_host_ip(&addr, m_Ip.c_str()) < 0)
        {
            return false;
        }

        auto* peer = enet_host_connect(m_Client, &addr, DEFAULT_CHANNEL_COUNT, 0);
        if (!peer)
        {
            return false;
        }

        ENetEvent event;
        if (enet_host_service(m_Client, &event, m_ConnectionTimeout) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        {
            // Connection succeeded.
            m_ServerPeer = event.peer;
            Event_OnConnect();
            return true;
        }
        else
        {
            // Connection failed.
            enet_peer_reset(peer);
            return false;
        }
    }

    bool Client::IsConnected() const noexcept
    {
        return m_ServerPeer != nullptr;
    }

    void Client::Disconnect() noexcept
    {
        using namespace std::chrono_literals;
        using clock = std::chrono::high_resolution_clock;

        if (IsConnected())
        {
            enet_peer_disconnect(m_ServerPeer, 0);

            const auto tp1 = clock::now();
            while (m_ServerPeer.load() != nullptr)
            {
                const auto tp2 = clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count() > m_ConnectionTimeout)
                {
                    enet_peer_reset(m_ServerPeer.load());
                    m_ServerPeer.store(nullptr);
                }
            }
        }
    }

    void Client::Update()
    {
        if (m_Client)
        {
            ENetEvent event;
            while (enet_host_service(m_Client, &event, Network::Defaults::CLIENT_RECEIVE_TIMEOUT) > 0)
            {
                switch (event.type)
                {
                    case ENET_EVENT_TYPE_DISCONNECT:
                        m_ServerPeer = nullptr;
                        Event_OnDisconnect();
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        if (m_ServerPeer)
                            Event_OnReceive(
                                DataPacket{ .buffer = event.packet->data, .len = event.packet->dataLength });
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_NONE: break;
                    default: break;
                }
            }
        }
        else
        {
            throw std::runtime_error("Client is offline.");
        }
    }

    bool Client::Send(DataPacket& packet) const noexcept
    {
        if (m_Client)
        {
            ENetPacket* enet_packet = enet_packet_create(packet.buffer, packet.len, ENET_PACKET_FLAG_RELIABLE);
            const auto  result      = enet_peer_send(m_ServerPeer, Network::Defaults::CHANNEL_ID, enet_packet);
            if (result < 0)
            {
                // Send failed, dispose the packet and return false.
                enet_packet_destroy(enet_packet);
            }
            else
            {
                // Send succeeded.
                return true;
            }
        }
        return false;
    }


} // namespace my
