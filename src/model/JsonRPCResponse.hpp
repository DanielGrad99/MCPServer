#pragma once

#include <string>
#include <variant>
#include <cstdint>
#include <memory>

#include <boost/json/fwd.hpp>

struct JsonRPCResponse {
    
    struct Error {
        std::string message;
        int code;
    };

    JsonRPCResponse();
    ~JsonRPCResponse();
    JsonRPCResponse(const JsonRPCResponse&);
    JsonRPCResponse(JsonRPCResponse&&) noexcept;
    JsonRPCResponse& operator=(const JsonRPCResponse&);
    JsonRPCResponse& operator=(JsonRPCResponse&&) noexcept;

    bool IsNotification() const;

    std::variant<std::monostate, std::string, std::int64_t> id;
    std::variant<std::unique_ptr<boost::json::value>, Error> result;
};

void tag_invoke(boost::json::value_from_tag, boost::json::value&, const JsonRPCResponse&);
