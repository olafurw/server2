cmake_minimum_required(VERSION 2.6)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0") 

include_directories( . ../common/ )

add_executable(server
    ../common/sha256.cpp
    ../common/utils.cpp
    config.cpp
    server.cpp
    router.cpp
    listener.cpp
    responder.cpp
    request_parser.cpp
    main.cpp
)

target_link_libraries(
    server
    pthread
    dl
)