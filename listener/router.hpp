#ifndef ROUT_ROUTER
#define ROUT_ROUTER

#include <memory>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "utils.hpp"
#include "config.hpp"

#include "request_parser.hpp"

class router
{
public:
    router();
    ~router();
    
    void start();
    
    void on_request(request_parser&& r);
    
private:
    std::unique_ptr<config_storage> m_config;
    std::vector<request_parser> m_work;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_has_data;
};

#endif
