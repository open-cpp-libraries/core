# Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# Official repository: https://git.ocl.nekernel.org/core

cmake_minimum_required(VERSION 3.15...3.31)

project(
  AllocatorExample
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED)

add_executable(AllocatorExample example.cpp)

set_property(TARGET AllocatorExample PROPERTY CXX_STANDARD 20)
target_include_directories(AllocatorExample PUBLIC ../../include/)

if (NOT DEFINED LINUX)
	target_link_libraries(AllocatorExample PRIVATE Boost)
endif()


