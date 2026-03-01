
cmake_minimum_required(VERSION 3.15...3.31)

project(
  AllocatorExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(AllocatorExample example.cpp)

set_property(TARGET AllocatorExample PROPERTY CXX_STANDARD 20)
target_include_directories(AllocatorExample PUBLIC ../../include/)
target_link_libraries(AllocatorExample PRIVATE Boost)
