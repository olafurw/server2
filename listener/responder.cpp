#include "responder.hpp"

#include "response_header.hpp"

responder::responder()
{

}

responder::~responder()
{

}

void responder::start()
{
    std::cout << "[Responder] Starting" << std::endl;
    
    std::vector<response> work;
    
    std::cout << "[Responder] Started" << std::endl;
    
    while(true)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [&]{ return m_has_data; });
            
            work.swap(m_work);
            
            m_has_data = false;
        }
        
        for(auto&& r : work)
        {
            response_header resp(r.m_data);
            
            write(r.m_socket, resp.m_response.c_str(), resp.m_response.size());
            close(r.m_socket);
        }
        
        work.clear();
    }
}

void responder::on_data(const int socket, std::string&& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_has_data = true;
    
    response r;
    r.m_data = data;
    r.m_socket = socket;
    
    m_work.emplace_back(r);
    
    m_cv.notify_all();
}
