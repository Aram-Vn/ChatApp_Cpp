#ifndef SERVER_CHATSERVER_H
#define SERVER_CHATSERVER_H

#include "../headers/Server.h"

struct ConnectedChatClient
{
    std::optional<std::string> name;
    const my::Client*          client;
};

class ChatServer : public my::Server
{
private:
    std::vector<ConnectedChatClient>::iterator GetClient(const my::Client& client) noexcept;

private:
    void Event_OnInit() override;
    void Event_OnClientConnect(const my::Client& client) override;
    void Event_OnClientDisconnect(const my::Client& client) override;
    void Event_OnReceive(const my::Client& client, const my::DataPacket& packet) override;

private:
    std::vector<ConnectedChatClient> m_Clients;
};
#endif // SERVER_CHATSERVER_H