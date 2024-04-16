project("Server")

file(GLOB_RECURSE CHATAPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CHATAPP_HEADERS "headers/*.h")

add_executable(chatserver ${CHATAPP_SOURCES} ${CHATAPP_HEADERS})
target_compile_options(chatserver PRIVATE -Wall -Werror -fsanitize=address -fsanitize=undefined)

target_link_libraries(chatserver enet)
target_include_directories(chatserver PRIVATE "${VENDOR_DIR}/enet/include/")
target_include_directories(chatserver PRIVATE "${COMMON_INCLUDE_DIR}")
