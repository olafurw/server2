#ifndef SERV_STATIC_FILE
#define SERV_STATIC_FILE

#include <string>

#include "utils.hpp"

class static_file
{
public:
    static_file(const std::string& filename);
    ~static_file();
    
    std::string m_data;

private:
};

#endif
