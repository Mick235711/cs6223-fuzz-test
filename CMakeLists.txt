cmake_minimum_required(VERSION 3.19)
project(first_fuzz_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-ld_classic -stdlib=libc++ -lc++abi")

add_subdirectory(fuzztest)

enable_testing()

include(GoogleTest)

add_executable(
    range_property
    range_property.cpp
    range_property.hpp
    demangle.hpp
)

link_fuzztest(range_property)
gtest_discover_tests(range_property)

add_executable(
    range_view_type_test
    range_view_type_test.cpp
    range_property.hpp
    random_ranges.hpp
    demangle.hpp
    ../../range-v3/include/range/v3/all.hpp
)

target_include_directories(range_view_type_test PRIVATE ../../range-v3/include/)

link_fuzztest(range_view_type_test)
gtest_discover_tests(range_view_type_test)
