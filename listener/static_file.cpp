#include "static_file.hpp"

static_file::static_file(const std::string& filename)
{
    m_data = utils::file_to_string(filename);
}

static_file::~static_file()
{

}
