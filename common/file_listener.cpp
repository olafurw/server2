#include "file_listener.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>

file_listener::file_listener(const std::string& path)
{
    m_event_size = sizeof(inotify_event);
    m_buffer_size = 1024 * (m_event_size + 16);

    m_buffer = new char[m_buffer_size];

    m_descriptor = inotify_init();
    m_watch = inotify_add_watch(m_descriptor, path.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
    
    m_create_set = false;
    m_modify_set = false;
    m_delete_set = false;
    
    m_running = true;
    m_thread = std::thread(&file_listener::run, this);
}

void file_listener::set_create(std::function<void(std::string)> c)
{
    m_create = c;
    m_create_set = true;
}

void file_listener::set_modify(std::function<void(std::string)> m)
{
    m_modify = m;
    m_modify_set = true;
}

void file_listener::set_delete(std::function<void(std::string)> d)
{
    m_delete = d;
    m_delete_set = true;
}

file_listener::~file_listener()
{
    delete [] m_buffer;
    close(m_descriptor);
    
    std::lock_guard<std::mutex> lock(m_mutex);
    m_running = false;
}

void file_listener::run()
{
    while(true)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            if(!m_running)
            {
                break;
            }
        }
        
        const int length = read(m_descriptor, m_buffer, m_buffer_size);
        int index = 0;

        while(index < length)
        {
            inotify_event* event = (inotify_event*)&m_buffer[index];
            if(event->len > 0)
            {
                const bool is_create = event->mask & IN_CREATE;
                const bool is_modify= event->mask & IN_MODIFY;
                const bool is_delete = event->mask & IN_DELETE;
                const bool is_directory = event->mask & IN_ISDIR;
                const bool is_file = !is_directory;

                if(m_create_set && is_create && is_file)
                {
                    m_create(event->name);
                }
                else if(m_modify_set && is_modify && is_file)
                {
                    m_modify(event->name);
                }
                else if(m_delete_set && is_delete && is_file)
                {
                    m_delete(event->name);
                }
            }
            index += m_event_size + event->len;
        }
    }
}
