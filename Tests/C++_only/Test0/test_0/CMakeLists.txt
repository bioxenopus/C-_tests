cmake_minimum_required(VERSION 3.5)

project(test_0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_0 test.cpp)

install(TARGETS test_0
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
