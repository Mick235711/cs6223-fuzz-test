cmake_minimum_required(VERSION 3.19)
project(first_fuzz_project)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(fuzztest)

enable_testing()

include(GoogleTest)

add_executable(
    range_property
    range_property.cpp
)

link_fuzztest(range_property)
gtest_discover_tests(range_property)
