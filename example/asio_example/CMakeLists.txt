
cmake_minimum_required(VERSION 3.15...3.31)

project(
  AsioExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(AsioExample example.cpp)

set_property(TARGET AsioExample PROPERTY CXX_STANDARD 20)
target_include_directories(AsioExample PUBLIC ../../include/)

if (NOT DEFINED LINUX)
target_link_libraries(AsioExample PRIVATE Boost Core Asio)
endif ()
