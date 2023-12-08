cmake_minimum_required(VERSION 3.22)
project(LoxInterpreter VERSION 1.0)
set(CMAKE_BUILD_TYPE Debug)

add_executable(LoxApp main.cpp Lox.cpp Token.cpp Scanner.cpp)

set_target_properties(LoxApp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
