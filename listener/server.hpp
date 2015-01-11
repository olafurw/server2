#ifndef SERVER
#define SERVER

#include <thread>
#include <mutex>

#include "listener.hpp"
#include "router.hpp"
#include "responder.hpp"

class server
{
public:
    server();
    ~server();
    
private:
    void listener_thread();
    void router_thread();
    void responder_thread();
    
    std::thread m_listener_thread;
    listener m_listener;
    
    std::thread m_router_thread;
    router m_router;
    
    std::thread m_responder_thread;
    responder m_responder;
};

#endif
