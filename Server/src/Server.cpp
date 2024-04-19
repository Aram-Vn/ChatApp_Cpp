#include "../headers/Server.h"
#include "Packet.h"
#include "enet/enet.h"
#include <stdexcept>

namespace my {
    static bool operator==(const ENetAddress& lhv, const ENetAddress& rhv) noexcept
    {
        return lhv.host == rhv.host && lhv.port == rhv.port;
    }

    bool Server::IsRunning() const noexcept
    {
        return m_Running;
    }

    const std::list<ServerClient>& Server::GetConnectedClients() const noexcept
    {
        return m_ConnectedClients;
    }

    Server::~Server() noexcept
    {
        m_Running = false;
        if (m_Host)
        {
            enet_host_destroy(m_Host);
        }
    }

    bool Server::Init(const std::uint16_t port) noexcept
    {
        m_EndPoint.host = ENET_HOST_ANY;
        m_EndPoint.port = port;

        m_Host = enet_host_create(&m_EndPoint, Network::Max::CLIENT_COUNT, Network::Max::CHANNEL_COUNT, 0, 0);
        if (m_Host)
        {
            m_Running = true;
            Event_OnInit();
            return true;
        }
        return false;
    }

    void Server::Update()
    {
        while (enet_host_service(m_Host, &m_Event, Network::Defaults::TIMEOUT))
        {
            switch (m_Event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: {
                    m_ConnectedClients.emplace_front(ServerClient{ m_Event.peer });
                    Event_OnClientConnect(m_ConnectedClients.front());
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    auto it = std::find_if(m_ConnectedClients.begin(), m_ConnectedClients.end(),
                                           [this](const ServerClient& elem)
                                           { return static_cast<ENetAddress>(elem) == m_Event.peer->address; });

                    if (it != m_ConnectedClients.end())
                    {
                        Event_OnClientDisconnect(*it);
                        m_ConnectedClients.erase(it);
                    }
                    else
                    {
                        throw std::runtime_error("A non-existing client is trying to disconnect!!!");
                    }
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    auto it = std::find_if(m_ConnectedClients.begin(), m_ConnectedClients.end(),
                                           [this](const ServerClient& elem)
                                           { return static_cast<ENetAddress>(elem) == m_Event.peer->address; });

                    if (it != m_ConnectedClients.end())
                    {
                        Event_OnReceive(
                            *it, DataPacket{ .buffer = m_Event.packet->data, .len = m_Event.packet->dataLength });
                    }
                    else
                    {
                        throw std::runtime_error("A non-existing client is trying to send a packet!!!.");
                    }

                    break;
                }
                default: break;
            }
        }
    }

    bool Server::Send(const ServerClient& client, DataPacket& packet)
    {
        if (client.GetPeer())
        {
            ENetPacket* enet_packet = enet_packet_create(packet.buffer, packet.len, ENET_PACKET_FLAG_RELIABLE);
            const auto  result      = enet_peer_send(client.GetPeer(), Network::Defaults::CHANNEL_ID, enet_packet);
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
