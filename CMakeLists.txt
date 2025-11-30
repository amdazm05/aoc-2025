cmake_minimum_required(VERSION 3.8...3.16)
project(aoc-2025 VERSION 0.1 LANGUAGES CXX)

set(PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(CONTRIB_DIR ${PROJECT_DIR}/contrib)

# Adds submodules to build
add_subdirectory(${CONTRIB_DIR}/catch2)

