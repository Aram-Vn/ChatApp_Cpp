#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <enet/enet.h>
#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <string_view>
#include <thread>
#include <vector>

namespace my {
    constexpr auto DEFAULT_CHANNEL_COUNT = 1;
}
