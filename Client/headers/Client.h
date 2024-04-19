#ifndef CLIENT_H
#define CLIENT_H

#include <Common.h>
#include <Packet.h>

namespace Network {

    namespace Defaults {

        constexpr int CLIENT_RECEIVE_TIMEOUT = 500;
        constexpr int CONNECTION_TIMEOUT     = 5000;
        constexpr int CHANNEL_ID             = 0;
        constexpr int PEER_COUNT             = 1;
        constexpr int PEER_CHANNEL_LIMIT     = 1;
        constexpr int INCOMING_BAND_WIDTH    = 0; // unlimited bandwidth
        constexpr int OUTGOING_BAND_WIDTH    = 0; // unlimited bandwidth

    } // namespace Defaults

} // namespace Network

namespace my {
    class Client
    {
    public:
        Client();                   //
        virtual ~Client() noexcept; //

    public:
        bool IsConnected() const noexcept;

    public:
        bool Connect(const std::string_view ip, const std::uint16_t port,
                     const std::uint16_t timeout = Network::Defaults::CLIENT_RECEIVE_TIMEOUT) noexcept; //
        void Disconnect() noexcept;
        void Update();
        bool Send(DataPacket& packet) const noexcept;

    protected:
        virtual void Event_OnReceive(const DataPacket& packet) = 0;
        virtual void Event_OnConnect()                         = 0;
        virtual void Event_OnDisconnect()                      = 0;

    private:
        ENetHost*              m_Client = nullptr;
        std::atomic<ENetPeer*> m_ServerPeer;
        std::string            m_Ip;
        std::uint16_t          m_Port;
        std::uint16_t          m_ConnectionTimeout = Network::Defaults::CONNECTION_TIMEOUT;
    };
} // namespace my

#endif // CLIENT_H
