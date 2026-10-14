cmake_minimum_required(VERSION 3.16)
project(DerivativesPricingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(option src/Option.cpp)
target_include_directories(option PUBLIC include)
target_compile_options(option PRIVATE -Wall -Wextra)

add_executable(pricer src/main.cpp)
target_link_libraries(pricer PRIVATE option)