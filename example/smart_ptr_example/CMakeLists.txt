
cmake_minimum_required(VERSION 3.15...3.31)

project(
  SmartPtrExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(SmartPtrExample example.ex.cpp)

set_property(TARGET SmartPtrExample PROPERTY CXX_STANDARD 20)
target_include_directories(SmartPtrExample PUBLIC ../../include/)
target_link_libraries(SmartPtrExample PRIVATE Boost)
