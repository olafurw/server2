#ifndef SERV_RESPONSE
#define SERV_RESPONSE

#include <string>
#include <sstream>

class response_header
{
public:
    response_header(const std::string& data);
    ~response_header();
    
    std::string m_response;
};

#endif
