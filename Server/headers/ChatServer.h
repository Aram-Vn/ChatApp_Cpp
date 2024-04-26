#ifndef CHATAPP_CPP_SERVER_HEADERS_CHATSERVER_H
#define CHATAPP_CPP_SERVER_HEADERS_CHATSERVER_H

#include "Server.h"

    struct ChatClient
{
    std::optional<std::string> name;
    const my::ServerClient*    client;
};

class ChatServer : public my::Server
{
private:
    std::vector<ChatClient>::iterator GetClient(const my::ServerClient& client) noexcept;

private:
    void Event_OnInit() override;
    void Event_OnClientConnect(const my::ServerClient& client) override;
    void Event_OnClientDisconnect(const my::ServerClient& client) override;
    void Event_OnReceive(const my::ServerClient& client, const my::DataPacket& packet) override;

private:
    std::vector<ChatClient> m_Clients;
};
#endif // CHATAPP_CPP_SERVER_HEADERS_CHATSERVER_H