#include <iostream>

#include <boost/json.hpp>

int main() {
    std::cerr << "hello!" << std::endl;

    auto jvalue = boost::json::parse("{ \"key\": \"value\" }");

    if (!jvalue.is_object()) {
        std::cerr << "Invalid object" << std::endl;
        return 1;
    }

    auto& jobject = jvalue.as_object();

    std::cerr << "jobject.count(\"key\") == " << jobject.count("key") << std::endl;
    std::cerr << "jobject.at(\"key\") == " << jobject.at("key") << std::endl;
    std::cerr << "jobject.at(\"key\").is_string() == " << jobject.at("key").is_string() << std::endl;
    std::cerr << "jobject.at(\"key\").as_string() == " << jobject.at("key").as_string() << std::endl;
    
    std::cerr << std::endl;

    std::cerr << "jobject.count(\"key1\") == " << jobject.count("key1") << std::endl;
    std::cerr << "jobject.if_contains(\"key1\") == " << jobject.if_contains("key1") << std::endl;

    try {
        std::cerr << "jobject.at(\"key1\") == " << jobject.at("key1") << std::endl;
    }
    catch (const boost::system::system_error& err) {
        std::cerr << "jobject.at(\"key1\") == " << err.what() << std::endl;
    }

    jobject["key1"];
    std::cerr << "jobject[\"key1\"]" << std::endl;
    std::cerr << "jobject.count(\"key1\") == " << jobject.count("key1") << std::endl;
    std::cerr << "jobject.if_contains(\"key1\") == " << jobject.if_contains("key1") << std::endl;

    std::error_code err;
    jvalue = boost::json::parse("{ \"key\": ", err);
    if (err) {
        std::cerr << err.message() << std::endl;
    }

    err.clear();
    auto jvalue1 = boost::json::parse("{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"tools/list\"}", err);
    if (err) {
        std::cerr << err.message() << std::endl;
        return 1;
    }

    if (!jvalue1.if_object()) {
        std::cerr << "Not a JSON object" << std::endl;
        return 1;
    }

    auto& jobject1 = jvalue1.as_object();

    if (!jobject1.if_contains("method")) {
        std::cerr << "method string does not exist" << std::endl;
        return 1;
    }

    if (!jobject1.at("method").is_string()) {
        std::cerr << "method field is not a string" << std::endl;
        return 1;
    }

    std::cerr << "Method: " << jobject1.at("method").as_string() << std::endl;

    return 0;
}
