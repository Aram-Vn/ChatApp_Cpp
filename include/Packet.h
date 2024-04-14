#ifndef INCLUDE_PACKET_H
#define iINCLUDE_PACKET_H

#include "Common.h"

namespace my {
    struct DataPacket
    {
        std::uint8_t* buffer;
        std::size_t   len;
    };
} // namespace my

#endif // INCLUDE_PACKET_H