#include "server.hpp"

#include <iostream>

server::server()
{
    std::cout << "[Server] Starting." << std::endl;

    m_listener.request_callback(
        std::bind(&router::on_request, &m_router, std::placeholders::_1)
    );
    
    m_router.data_callback(
        std::bind(&responder::on_data, &m_responder, std::placeholders::_1, std::placeholders::_2)
    );
    
    m_listener_thread = std::thread(&server::listener_thread, this);
    m_router_thread = std::thread(&server::router_thread, this);
    m_responder_thread = std::thread(&server::responder_thread, this);
    
    m_listener_thread.join();
    m_router_thread.join();
    m_responder_thread.join();
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

void server::responder_thread()
{
    std::cout << "[Server] Starting responder thread." << std::endl;
    m_responder.start();
}
