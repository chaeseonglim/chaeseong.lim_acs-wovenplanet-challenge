cmake_minimum_required(VERSION 3.10.0)

project(Challenge LANGUAGES CXX)

enable_testing()

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(tests)
