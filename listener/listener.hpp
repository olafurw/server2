#ifndef SERV_LISTENER
#define SERV_LISTENER

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <net/route.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <memory>
#include <map>
#include <vector>
#include <mutex>
#include <functional>
#include <condition_variable>

#include "request_parser.hpp"

class listener
{
public:
    listener();
    ~listener();
    
    void start();
    
    void request_callback(std::function<void(request_parser)> cb);

private:
    void handle_events();
    void handle_event(const epoll_event& event);
    
    void handle_data();
    
    void read_request(int sockfd, std::string& buffer_str);

    void set_address_info();
    void create_socket();

    void set_socket_reusable();
    void set_socket_bind();
    void set_socket_non_blocking();
    void set_socket_listen();

    void create_epoll();
    void set_epoll_interface(int socket);
    
    std::string m_port;
    addrinfo* m_address_info;
    epoll_event* m_epoll_events;
    int m_id;
    int m_socket;
    int m_epoll;
    int m_connection_queue_size;
    int m_read_size;
    
    std::function<void(request_parser)> m_cb;
};

#endif
