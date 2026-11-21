cmake_minimum_required(VERSION 3.16)
project(DerivativesPricingEngine LANGUAGES CXX)
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(option src/Option.cpp)
target_include_directories(option PUBLIC include)
target_compile_options(option PRIVATE -Wall -Wextra)

add_library(BinomialTree src/BinomialTree.cpp)
target_include_directories(BinomialTree PUBLIC include)
target_compile_options(BinomialTree PRIVATE -Wall -Wextra)

add_library(Validation src/Validation.cpp)
target_include_directories(Validation PUBLIC include)
target_compile_options(Validation PRIVATE -Wall -Wextra)

add_executable(pricer src/main.cpp)
target_link_libraries(pricer PRIVATE option)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(option_tests tests/test_option.cpp)
target_link_libraries(option_tests PRIVATE option GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(option_tests)


add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE option)