#ifndef SERVER_CHATSERVER_H
#define SERVER_CHATSERVER_H

#include "../headers/Server.h"

class ChatServer : public my::Server
{
private:
    void Event_OnInit() override;
    void Event_OnClientConnect(const my::Client& client) override;
    void Event_OnClientDisconnect(const my::Client& client) override;
    void Event_OnReceive(const my::Client& client, const my::DataPacket& packet) override;
};
#endif // SERVER_CHATSERVER_H