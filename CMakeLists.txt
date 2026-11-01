cmake_minimum_required(VERSION 3.21)

project(MCPServer
    VERSION 1.0
    DESCRIPTION "A sample MCP server"
    LANGUAGES CXX
    )

find_package(Boost CONFIG REQUIRED COMPONENTS json)

add_executable(mcpserver)

target_sources(mcpserver PRIVATE
    "src/main.cpp"
    "src/transport/StdioTransport.cpp"
    "src/model/JsonRPCRequest.cpp"
     "src/model/JsonRPCResponse.cpp")

target_compile_features(mcpserver PRIVATE cxx_std_20)

target_link_libraries(mcpserver PRIVATE Boost::json)

target_include_directories(mcpserver PRIVATE src)

target_compile_options(mcpserver PRIVATE /W4 /utf-8)
