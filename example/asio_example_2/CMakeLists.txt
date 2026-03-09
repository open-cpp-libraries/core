# (C) 2026 Amlal El Mahrouss

cmake_minimum_required(VERSION 3.15...3.31)

project(
  AsioExample2
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(AsioExample2 example.cpp)

set_property(TARGET AsioExample2 PROPERTY CXX_STANDARD 20)
target_include_directories(AsioExample2 PUBLIC ../../include/)

if (NOT DEFINED LINUX)
target_link_libraries(AsioExample2 PRIVATE Boost Core Asio Process)
else()
target_link_libraries(AsioExample2 PRIVATE boost_process)
endif ()
