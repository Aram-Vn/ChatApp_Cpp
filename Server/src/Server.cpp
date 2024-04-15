#include "Server.h"
#include "Packet.h"
#include "enet/enet.h"
#include <stdexcept>

namespace my {
    static bool operator==(const ENetAddress& lhv, const ENetAddress& rhv) noexcept
    {
        return lhv.host == rhv.host && lhv.port == rhv.port;
    }

    Server::~Server() noexcept
    {
        m_Running = false;
        if (m_Host)
            enet_host_destroy(m_Host);
    }

    bool Server::Init(const std::uint16_t port) noexcept
    {
        m_EndPoint.host = ENET_HOST_ANY;
        m_EndPoint.port = port;

        m_Host = enet_host_create(&m_EndPoint, Server::MAX_CLIENT_COUNT, Server::MAX_CHANNEL_COUNT, 0, 0);
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
        while (enet_host_service(m_Host, &m_Event, Server::DEFAULT_TIMEOUT))
        {
            switch (m_Event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: {
                    m_ConnectedClients.emplace_front(m_Event.peer, "Bob");
                    Event_OnClientConnect(m_ConnectedClients.front());
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    auto it = std::find_if(m_ConnectedClients.begin(), m_ConnectedClients.end(),
                                           [this](auto& e) { return (ENetAddress)e == m_Event.peer->address; });

                    if (it != m_ConnectedClients.end())
                    {
                        Event_OnClientDisconnect(*it);
                        m_ConnectedClients.erase(it);
                    }
                    else
                        throw std::runtime_error("VERY BAD!!! abort abort");
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    auto it = std::find_if(m_ConnectedClients.begin(), m_ConnectedClients.end(),
                                           [this](auto& e) { return (ENetAddress)e == m_Event.peer->address; });

                    if (it != m_ConnectedClients.end())
                    {
                        Event_OnReceive(
                            *it, DataPacket{ .buffer = m_Event.packet->data, .len = m_Event.packet->dataLength });
                    }
                    else
                        throw std::runtime_error("Somewhere something went wrong.");
                    break;
                }
                default: break;
            }
        }
    }

} // namespace my
