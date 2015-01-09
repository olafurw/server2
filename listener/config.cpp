#include "config.hpp"

config_storage::config_storage(const std::string& path)
{
    const auto lines = utils::file_to_array(path);
    
    for(const auto& route : lines)
    {
        const auto line = utils::split_string(route, ' ');

        config c;
        c.path = line[2];
        c.type = static_route;
        m_routes[line[1]] = c;
    }
}

config_storage::~config_storage()
{

}

config config_storage::get(const std::string& key)
{
    return m_routes[key];
}
