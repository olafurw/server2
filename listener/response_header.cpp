#include "response_header.hpp"

response_header::response_header(const std::string& data)
{
    std::stringstream ss;
    ss << "HTTP/1.0 200 OK\n";
    ss << "Server: sammy v0.1\n";
    ss << "MIME-version: 1.0\n";
    ss << "Content-type: text/html\n";
    //ss << access_control();
    ss << "Set-Cookie: LOL_SESSION=abc123; Expires=Wed, 16 Nov 2015 12:34:56 GMT\n";
    ss << "Last-Modified: Thu 1 Jan 1970 00:00:00 PM EST\n";
    ss << "Content-Length: " << data.size() << "\n\n";
    ss << data << "\n\n";
    
    m_response = ss.str();
}

response_header::~response_header()
{

}
