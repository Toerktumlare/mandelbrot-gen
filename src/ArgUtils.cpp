#include <string>
#include <iostream>

#include "ArgUtils.h"

void ArgUtils::print(const char *value) {
    std::cout << value << std::endl;
}

std::string ArgUtils::extractValue(std::string value) {
    return value.substr(2, value.size());
}

bool ArgUtils::isNumber(const std::string &value) {
    return !value.empty() || std::find_if(value.begin(), value.end(), [] (char c) {
        return !std::isdigit(c);
    }) == value.end();
}
