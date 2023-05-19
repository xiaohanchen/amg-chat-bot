cmake_minimum_required(VERSION 3.25)
project(amg_chat_bot)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
    src
)

add_executable(ServerTestExe test/server_test.cpp)
add_executable(ClientTestExe test/client_test.cpp)

target_link_libraries(ServerTestExe
    ChatLib
)

target_link_libraries(ClientTestExe
    ChatLib
)