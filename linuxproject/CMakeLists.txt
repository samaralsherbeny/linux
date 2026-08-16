cmake_minimum_required(VERSION 3.16)
project(LinuxSystemManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(linux_system_manager
    src/main.cpp
    src/SystemManager.cpp
    src/ProcessManager.cpp
    src/FileManager.cpp
    src/NetworkManager.cpp
    src/IPCManager.cpp
    src/ThreadManager.cpp
)

target_compile_options(linux_system_manager PRIVATE -Wall -Wextra -Wpedantic)
