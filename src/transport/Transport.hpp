#pragma once

#include <functional>
#include <string>

class Transport {
public:
    virtual void Start(std::function<std::string(std::string)>) = 0;
};
