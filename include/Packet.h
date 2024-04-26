#ifndef CHATAPP_CPP_INCLUDE_PACKET_H
#define CHATAPP_CPP_INCLUDE_PACKET_H
#include "Common.h"

    namespace my {
    struct DataPacket
    {
        std::uint8_t* buffer;
        std::size_t   len;
    };
} // namespace my

#endif // CHATAPP_CPP_INCLUDE_PACKET_H