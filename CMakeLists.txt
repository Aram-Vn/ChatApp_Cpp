cmake_minimum_required(VERSION 3.20)
project("ChatApp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor")
set(COMMON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fsanitize=address -fsanitize=undefined")

if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
  add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json...")

  add_custom_target(copy_compile_commands ALL
                    DEPENDS ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()

add_subdirectory("${VENDOR_DIR}/enet" "${CMAKE_BINARY_DIR}/enet")
add_subdirectory("Server")
add_subdirectory("Client")
