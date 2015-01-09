#include "server.hpp"

#include <iostream>

server::server()
{
    std::cout << "[Server] Starting." << std::endl;

    m_listener.request_callback(
        std::bind(&router::on_request, &m_router, std::placeholders::_1)
    );    
    
    m_listener_thread = std::thread(&server::listener_thread, this);
    m_router_thread = std::thread(&server::router_thread, this);
    
    m_listener_thread.join();
    m_router_thread.join();
}

server::~server()
{
    
}

void server::router_thread()
{
    std::cout << "[Server] Starting router thread." << std::endl;
    m_router.start();
}

void server::listener_thread()
{
    std::cout << "[Server] Starting listener thread." << std::endl;
    m_listener.start();
}
