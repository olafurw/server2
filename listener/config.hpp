#ifndef ROUT_CONFIG
#define ROUT_CONFIG

#include <map>
#include <string>
#include <iostream>

#include "utils.hpp"

enum route_type
{
    static_route
};

class config
{
public:
    std::string path;
    route_type type;
};

class config_storage
{
public:
    config_storage(const std::string& path);
    ~config_storage();
    
    config get(const std::string& key);
    
private:
    std::map<std::string, config> m_routes;
};

#endif
