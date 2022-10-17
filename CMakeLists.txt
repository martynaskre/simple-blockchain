cmake_minimum_required(VERSION 3.21)
project(Blockchain)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O2")
endif()

set(SOURCE_FILES main.cpp)
add_executable(Blockchain ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(Blockchain Blockchain_src)

set(CLI_SOURCE_FILES cli.cpp)
add_executable(Blockchain_cli ${CLI_SOURCE_FILES})

target_link_libraries(Blockchain_cli Blockchain_src)