
cmake_minimum_required(VERSION 3.15...3.31)

project(
  MathExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(MathExample example.ex.cpp)

set_property(TARGET MathExample PROPERTY CXX_STANDARD 20)
target_include_directories(MathExample PUBLIC ../../include/)
