#pragma once

#include <string>
#include <complex>

class ArgUtils {
public:
    static std::string extractValue(const std::string &value);

    static void print(const char* value);
    
    static bool isNumber(const std::string &value);
    
};
