#pragma once

#include <iostream>

#include "Transport.hpp"

class StdioTransport : public Transport {
public:

    StdioTransport(std::istream& in, std::ostream& out);

    void Start(std::function<std::string(std::string)>) override;

private:
    std::istream& in;
    std::ostream& out;
};
