project("Client")

file(GLOB_RECURSE CHATAPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CHATAPP_HEADERS "headers/*.h")

add_executable(chatclient ${CHATAPP_SOURCES} ${CHATAPP_HEADERS})

target_compile_options(chatclient PRIVATE -Wall -Werror -fsanitize=address -fsanitize=undefined)

target_link_libraries(chatclient enet)
target_include_directories(chatclient PRIVATE "${VENDOR_DIR}/enet/include/")
target_include_directories(chatclient PRIVATE "${COMMON_INCLUDE_DIR}")
