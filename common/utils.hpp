#ifndef UTILITIES
#define UTILITIES

#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <memory>
#include <random>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace utils
{
    std::string sha256(const std::string& data);
    std::string stacktrace(int skip = 1);

    // Trimming
    // http://stackoverflow.com/a/217605/22459
    // Evan Teran
    std::string& ltrim(std::string& s);
    std::string& rtrim(std::string& s);
    std::string& trim(std::string& s);
    std::string ltrim(const std::string& s);
    std::string rtrim(const std::string& s);
    std::string trim(const std::string& s);

    std::vector<std::string> split_string(const std::string& str, const char token, const bool skip_empty = false);

    // File to string
    // http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
    std::string file_to_string(const std::string& filename);

    std::vector<std::string> file_to_array(const std::string& filename, char token = '\n');
    void write_to_file(const std::string& filename, const std::string& content);
}

#endif
