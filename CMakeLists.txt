cmake_minimum_required(VERSION 3.15)

project(MCPServer
    VERSION 1.0
    DESCRIPTION "A sample MCP server"
    LANGUAGES CXX
    )

add_executable(mcpserver src/main.cpp)
target_compile_features(mcpserver PRIVATE cxx_std_20)
