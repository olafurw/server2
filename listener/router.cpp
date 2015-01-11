#include "router.hpp"

#include <iostream>

router::router()
{
    m_has_data = false;
}

void router::start()
{
    std::cout << "[Router] Starting" << std::endl;
    
    m_config = std::unique_ptr<config_storage>(new config_storage(
        "/home/olafurw/server/config/routes"
    ));
    
    std::vector<request_parser> work;
    
    std::cout << "[Router] Started" << std::endl;
    
    while(true)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [&]{ return m_has_data; });
            
            work.swap(m_work);
            
            m_has_data = false;
        }
        
        for(auto&& request : work)
        {
            config c = m_config->get(request.get_path());
            
            m_cb(request.get_socket(), "asdf");
        }
        
        work.clear();
    }
}

void router::data_callback(std::function<void(const int, std::string)> cb)
{
    m_cb = cb;
}

void router::on_request(request_parser&& r)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_has_data = true;
    
    m_work.emplace_back(r);
    
    m_cv.notify_all();
}

router::~router()
{

}