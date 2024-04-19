#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "Client.h"

class ChatClient : public my::Client
{
public:
    ChatClient(const std::string_view nick);
    ChatClient();
    ~ChatClient() = default;

public:
    const std::string& Get_Nick() const;
    bool               SendString(const std::string_view string) const noexcept;

protected:
    void Event_OnConnect() override;
    void Event_OnDisconnect() override;
    void Event_OnReceive(const my::DataPacket& data) override;

private:
    std::string m_Nick;
};

#endif // CHATCLIENT_H
