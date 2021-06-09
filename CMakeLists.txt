cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp models/data.h utils/data_io_utils.h utils/file_io_utils.h)