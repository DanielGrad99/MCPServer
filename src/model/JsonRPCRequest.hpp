#pragma once

#include <string>
#include <variant>
#include <cstdint>
#include <memory>

#include <boost/json/fwd.hpp>

class JsonRPCRequest {
public:

    JsonRPCRequest();
    ~JsonRPCRequest();
    JsonRPCRequest(const JsonRPCRequest&);
    JsonRPCRequest(JsonRPCRequest&&) noexcept;
    JsonRPCRequest& operator=(const JsonRPCRequest&);
    JsonRPCRequest& operator=(JsonRPCRequest&&) noexcept;

    static JsonRPCRequest DeserializeFromJson(const std::string&);

    //std::string jsonrpc = "2.0";
    std::string method;
    std::variant<std::monostate, std::string, std::int64_t> id;
    std::unique_ptr<boost::json::value> params;
};

JsonRPCRequest tag_invoke(boost::json::value_to_tag<JsonRPCRequest>, boost::json::value const& jvalue);
