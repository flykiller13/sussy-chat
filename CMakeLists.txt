cmake_minimum_required(VERSION 3.28)
project(sussy-chat VERSION 1.0.0)

# Set the C++ standard to match your library (e.g., C++23 for modern features)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch sussy-socket library
include(FetchContent)
FetchContent_Declare(
        sussy_socket
        GIT_REPOSITORY https://github.com/flykiller13/sussy-socket.git
        GIT_TAG main
)
FetchContent_MakeAvailable(sussy_socket)

# Server executable
add_executable(chat_server
        src/server_main.cpp
        src/ChatServer.cpp
)

# Client executable
add_executable(chat_client
        src/client_main.cpp
        src/ChatClient.cpp
)

# Link library
target_link_libraries(chat_server PRIVATE sussy_socket)
target_link_libraries(chat_client PRIVATE sussy_socket)

# Set include directories
target_include_directories(chat_server PRIVATE include)
target_include_directories(chat_client PRIVATE include)