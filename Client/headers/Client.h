#ifndef CLIENT_H
#define CLIENT_H

#include <Common.h>
#include <Packet.h>

namespace my {
    class Client
    {
    public:
        static constexpr auto DEFAULT_CLIENT_TIMEOUT     = 1000;
        static constexpr auto DEFAULT_CONNECTION_TIMEOUT = 5000;

    private:
        ENetHost*              m_Client = nullptr;
        std::atomic<ENetPeer*> m_ServerPeer;
        std::string            m_Ip;
        std::uint16_t          m_Port;

    public:
        Client();
        virtual ~Client() noexcept;

    public:
        bool IsConnected() const noexcept
        {
            return m_ServerPeer != nullptr;
        }

    public:
        bool Connect(const std::string_view ip, const std::uint16_t port,
                     const std::uint16_t timeout = DEFAULT_CLIENT_TIMEOUT) noexcept;
        void Disconnect() noexcept;
        void Update();
        bool Send(DataPacket& packet) const noexcept;

    protected:
        virtual void Event_OnReceive(const DataPacket& packet) = 0;
        virtual void Event_OnConnect()                         = 0;
        virtual void Event_OnDisconnect()                      = 0;
    };
} // namespace my

#endif // CLIENT_H
