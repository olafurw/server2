#ifndef SERVER
#define SERVER

#include <thread>
#include <mutex>

#include "listener.hpp"
#include "router.hpp"

class server
{
public:
    server();
    ~server();
    
private:
    void listener_thread();
    void router_thread();
    
    std::thread m_listener_thread;
    listener m_listener;
    
    std::thread m_router_thread;
    router m_router;
};

#endif
