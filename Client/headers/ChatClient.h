#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "Client.h"

class ChatClient : public my::Client
{
public:
    ChatClient();
    ~ChatClient() = default;

protected:
    void Event_OnConnect() override;
    void Event_OnDisconnect() override;
    void Event_OnReceive(const my::DataPacket& data) override;
};

#endif // CHATCLIENT_H
