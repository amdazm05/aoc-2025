cmake_minimum_required(VERSION 3.8...3.16)
project(aoc-2025 VERSION 0.1 LANGUAGES CXX)

# Top level Macros
set(PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(CONTRIB_DIR ${PROJECT_DIR}/contrib)
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SRC_DIR ${PROJECT_DIR}/src)
set(PROJECT_TEST_DIR ${PROJECT_DIR}/tests)
set(PROJECT_CMAKE_MOD_DIR ${PROJECT_DIR}/cmake)
set(COMPILER_CXX_VERSION cxx_std_23)

# For CMake Modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_CMAKE_MOD_DIR})

# Adds submodules to build
add_subdirectory(${CONTRIB_DIR}/catch2)
add_subdirectory(${PROJECT_SRC_DIR})
add_subdirectory(${PROJECT_TEST_DIR})

