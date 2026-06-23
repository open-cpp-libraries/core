# Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# Official repository: https://git.ocl.nekernel.org/core

cmake_minimum_required(VERSION 3.15...3.31)

project(
  AsioExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(AsioExample example.ex.cpp)

set_property(TARGET AsioExample PROPERTY CXX_STANDARD 20)
target_include_directories(AsioExample PUBLIC ../../include/)

if (NOT DEFINED LINUX)
target_link_libraries(AsioExample PRIVATE Boost Core Asio)
endif ()
