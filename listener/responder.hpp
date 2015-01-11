#ifndef SERV_RESPONDER
#define SERV_RESPONDER

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
#include <iostream>

class response
{
public:
    int m_socket;
    std::string m_data;
};

class responder
{
public:
    responder();
    ~responder();
    
    void start();
    
    void on_data(const int socket, std::string&& data);
    
private:
    std::vector<response> m_work;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_has_data;
};

#endif
