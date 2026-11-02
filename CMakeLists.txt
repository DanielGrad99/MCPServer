cmake_minimum_required(VERSION 3.21)

project(MCPServer
    VERSION 1.0
    DESCRIPTION "A sample MCP server"
    LANGUAGES CXX
    )

find_package(Boost CONFIG REQUIRED COMPONENTS json)

add_library(mcpserverlibrary STATIC
    "src/helper.cpp"
    "src/transport/StdioTransport.cpp"
    "src/model/JsonRPCRequest.cpp"
    "src/model/JsonRPCResponse.cpp")

target_compile_features(mcpserverlibrary PUBLIC cxx_std_20)
target_include_directories(mcpserverlibrary PUBLIC src)

target_link_libraries(mcpserverlibrary PRIVATE Boost::json)
target_compile_options(mcpserverlibrary PRIVATE /W4 /utf-8)

add_executable(mcpserver)

target_sources(mcpserver PRIVATE "src/main.cpp")

target_link_libraries(mcpserver PRIVATE mcpserverlibrary)
target_compile_options(mcpserver PRIVATE /W4 /utf-8)
