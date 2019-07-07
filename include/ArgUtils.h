#pragma once

#include <string>

class ArgUtils {
public:
    static std::string extractValue(std::string value);

    static void print(const char* value);
    
    static bool isNumber(const std::string &value);
};
