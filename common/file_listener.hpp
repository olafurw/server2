#ifndef UTILS_FILE_LISTENER
#define UTILS_FILE_LISTENER

#include <functional>
#include <string>
#include <thread>
#include <mutex>

class file_listener
{
public:
    file_listener(const std::string& path);
    ~file_listener();
    
    void set_create(std::function<void(std::string)> c);
    void set_modify(std::function<void(std::string)> m);
    void set_delete(std::function<void(std::string)> d);
    
private:
    void run();
    
    int m_event_size;
    int m_buffer_size;
    char* m_buffer;
    int m_descriptor;
    int m_watch;
    
    std::function<void(std::string)> m_create;
    bool m_create_set;
    
    std::function<void(std::string)> m_modify; 
    bool m_modify_set;
    
    std::function<void(std::string)> m_delete;
    bool m_delete_set;
    
    bool m_running;
    std::thread m_thread;
    std::mutex m_mutex;
};

#endif
