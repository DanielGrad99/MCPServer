#include "StdioTransport.hpp"

#include <string>

StdioTransport::StdioTransport(std::istream& in, std::ostream& out) : in(in), out(out) {}

void StdioTransport::Start(std::function<std::string(std::string)> callback) {

    std::string line, response;

    while (std::getline(in, line)) {
        
        if (line.empty()) {
            continue;
        }

        response = callback(line);

        if (response.empty()) {
            continue;
        }

        out << response << std::endl;
    }
}
