
cmake_minimum_required(VERSION 3.15...3.31)

project(
  OptionExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(OptionExample example.ex.cpp)

set_property(TARGET OptionExample PROPERTY CXX_STANDARD 20)
target_include_directories(OptionExample PUBLIC ../../include/)

if (DEFINED LINUX)
target_link_libraries(OptionExample PRIVATE Boost)
endif ()
