cmake_minimum_required(VERSION 3.16)
project(DerivativesPricingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pricer src/main.cpp src/Option.cpp)
target_include_directories(pricer PRIVATE include)
target_compile_options(pricer PRIVATE -Wall -Wextra)