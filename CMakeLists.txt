cmake_minimum_required(VERSION 3.28)
project(sussy-chat VERSION 1.0.0)

# Set the C++ standard to match your library (e.g., C++23 for modern features)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add 'sussy_socket' library target available to the project.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/sussy-socket/CMakeLists.txt")
    add_subdirectory(third_party/sussy-socket)
else()
    message(FATAL_ERROR "sussy-socket submodule not found! Did you run 'git submodule update --init'?")
endif()

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
# This allows us to use #include "ChatServer.h" instead of relative paths.
target_include_directories(chat_server PRIVATE include)
target_include_directories(chat_client PRIVATE include)