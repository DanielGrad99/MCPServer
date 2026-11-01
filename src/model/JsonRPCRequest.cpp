#include "JsonRPCRequest.hpp"

#include <utility>
#include <boost/json.hpp>

#include "JsonRPCError.hpp"

JsonRPCRequest::JsonRPCRequest() = default;
JsonRPCRequest::~JsonRPCRequest() = default;
JsonRPCRequest::JsonRPCRequest(JsonRPCRequest&&) noexcept = default;
JsonRPCRequest& JsonRPCRequest::operator=(JsonRPCRequest&&) noexcept = default;

JsonRPCRequest::JsonRPCRequest(const JsonRPCRequest& other) :
    method(other.method),
    id(other.id),
    params(other.params ? std::make_unique<boost::json::value>(*other.params) : nullptr)
    {}

JsonRPCRequest& JsonRPCRequest::operator=(const JsonRPCRequest& other) {
    return *this = JsonRPCRequest(other);
}

JsonRPCRequest JsonRPCRequest::DeserializeFromJson(const std::string& str) {

    std::error_code er;
    auto jvalue = boost::json::parse(str, er);

    if (er) {
        throw JsonRPCError("invalid JSON", -32700);
    }

    return boost::json::value_to<JsonRPCRequest>(jvalue);
}

JsonRPCRequest tag_invoke(boost::json::value_to_tag<JsonRPCRequest>, boost::json::value const& jvalue) {
    
    if (!jvalue.is_object()) {
        throw JsonRPCError("JSON value is not an object", -32600);
    }
    auto const& obj = jvalue.as_object();

    JsonRPCRequest request;

    auto jsonrpc = obj.if_contains("jsonrpc");
    if (!jsonrpc || !jsonrpc->is_string()) {
        throw JsonRPCError("jsonrpc is not present", -32600);
    }

    if (boost::json::value_to<std::string>(*jsonrpc) != "2.0") {
        throw JsonRPCError("jsonrpc is not 2.0", -32600);
    }

    auto method = obj.if_contains("method");
    if (!method) {
        throw JsonRPCError("method is missing", -32600);
    }
    if (!method->is_string()) {
        throw JsonRPCError("method must be a string", -32600);
    }

    request.method = boost::json::value_to<std::string>(*method);

    if (auto id = obj.if_contains("id"); id) {
        if (id->is_int64()) {
            request.id = boost::json::value_to<std::int64_t>(*id);
        } else if (id->is_string()) {
            request.id = boost::json::value_to<std::string>(*id);
        } else {
            throw JsonRPCError("id must be a number or string", -32600);
        }
    }

    if (auto params = obj.if_contains("params"); params) {

        if (!(params->is_object() || params->is_array())) {
            throw JsonRPCError("params must be an object or array", -32600);
        }

        request.params = std::make_unique<boost::json::value>(*params);
    }

    return request;
}
