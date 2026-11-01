#include "JsonRPCResponse.hpp"

#include <boost/json.hpp>

JsonRPCResponse::JsonRPCResponse() = default;
JsonRPCResponse::~JsonRPCResponse() = default;
JsonRPCResponse::JsonRPCResponse(JsonRPCResponse&&) noexcept = default;
JsonRPCResponse& JsonRPCResponse::operator=(JsonRPCResponse&&) noexcept = default;

JsonRPCResponse::JsonRPCResponse(const JsonRPCResponse& other) :
    id(other.id) {

    if (const JsonRPCResponse::Error* error = std::get_if<JsonRPCResponse::Error>(&other.result)) {
        result = *error;
    } else if (const std::unique_ptr<boost::json::value>* upp = std::get_if<std::unique_ptr<boost::json::value>>(&other.result)) {
        if (*upp) {
            result = std::make_unique<boost::json::value>(**upp);
        } else {
            result = nullptr;
        }
    }
}

JsonRPCResponse& JsonRPCResponse::operator=(const JsonRPCResponse& other) {
    return *this = JsonRPCResponse(other);
}

bool JsonRPCResponse::IsNotification() const {
    return std::holds_alternative<std::monostate>(id);
}

void tag_invoke(boost::json::value_from_tag, boost::json::value& jvalue, const JsonRPCResponse& jsonRPCResponse) {
    jvalue = {
        { "jsonrpc", "2.0" },
    };

    auto& jobject = jvalue.as_object();

    if (const auto str = std::get_if<std::string>(&jsonRPCResponse.id)) {
        jobject["id"] = *str;
    }
    else if (const auto i = std::get_if<std::int64_t>(&jsonRPCResponse.id)) {
        jobject["id"] = *i;
    }
    else {
        jobject["id"] = nullptr;
    }

    if (const auto er = std::get_if<JsonRPCResponse::Error>(&jsonRPCResponse.result)) {
        jobject["error"] = {
            { "code", er->code },
            { "message", er->message },
        };
    }
    else if (const auto ptr = std::get_if<std::unique_ptr<boost::json::value>>(&jsonRPCResponse.result)) {
        jobject["result"] = **ptr;
    }
}
