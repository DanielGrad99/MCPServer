#pragma once

#include <stdexcept>
#include <string>

struct JsonRPCError : public std::runtime_error {

    JsonRPCError(const std::string& s, int code) : std::runtime_error(s), code(code) {}
    JsonRPCError(const char* s, int code) : std::runtime_error(s), code(code) {}

    int code = -32603;
};
