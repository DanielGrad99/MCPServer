cmake_minimum_required(VERSION 3.21)

project(MCPServer
    VERSION 1.0
    DESCRIPTION "A sample MCP server"
    LANGUAGES CXX
    )

find_package(Boost CONFIG REQUIRED COMPONENTS json)

add_executable(mcpserver src/main.cpp)

target_compile_features(mcpserver PRIVATE cxx_std_20)

target_link_libraries(mcpserver PRIVATE Boost::json)
