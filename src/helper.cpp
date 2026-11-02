#include <iostream>
#include <exception>
#include <string>

#include <boost/json.hpp>

#include "transport/StdioTransport.hpp"
#include "model/JsonRPCRequest.hpp"
#include "model/JsonRPCResponse.hpp"
#include "model/JsonRPCError.hpp"

JsonRPCResponse compute(const JsonRPCRequest& request) {

    JsonRPCResponse response;

    //response.result = std::make_unique<boost::json::value>(request.method);

    std::string method = request.method;

    if (method == "ping") {
        response.result = std::make_unique<boost::json::value>(boost::json::object());
    }
    else {
        throw JsonRPCError("Method not found", -32601);
    }

    return response;
}

std::string callback(const std::string& str)
{

    JsonRPCRequest request;
    JsonRPCResponse response;

    try {
        request = JsonRPCRequest::DeserializeFromJson(str);
    }
    catch (const JsonRPCError& er) {
        response.result = JsonRPCResponse::Error{ er.what(), er.code };
    }
    catch (...) {
        response.result = JsonRPCResponse::Error{ "Unknown error", -32603 };
    }

    if (std::holds_alternative<JsonRPCResponse::Error>(response.result)) {
        response.id = request.id;
        return boost::json::serialize(boost::json::value_from(response));
    }

    try {
        response = compute(request);
    }
    catch (const JsonRPCError& er) {
        response.result = JsonRPCResponse::Error{ er.what(), er.code };
    }
    catch (...) {
        response.result = JsonRPCResponse::Error{ "Unknown error", -32603 };
    }

    response.id = request.id;

    if (response.IsNotification())
    {
        return "";
    }

    return boost::json::serialize(boost::json::value_from(response));

    //JsonRPCRequest request1 = request;

    //request1.params->as_object()["hi"] = "hello";

    //std::cout << boost::json::serialize(*request.params) << std::endl;
    //std::cout << boost::json::serialize(*request1.params) << std::endl;
}


void StartServer() {
    StdioTransport stdioTransport = StdioTransport(std::cin, std::cout);
    stdioTransport.Start(callback);
}
