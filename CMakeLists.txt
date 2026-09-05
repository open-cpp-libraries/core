# // ============================================================= //
# // Open C++ Libraries.
# // Copyright (C) 2025-2026, Amlal El Mahrouss, Ne.app, and OCL Authors, licensed under the BSL 1.0 license.
# // ============================================================= //

cmake_minimum_required(VERSION 3.22.1)

project(OCL_Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EXTENSIONS_CXX_OCL)
set(CMAKE_CXX_EXTENSIONS ON)
else()
set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Install OCL if given the instruction.
if (INSTALL_OCL)
   include(install_core.cmake)
endif()
