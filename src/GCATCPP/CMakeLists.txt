cmake_minimum_required(VERSION 3.10)
project(GCATCPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main_test.cpp codes/AbstractGenCode.cpp codes/StdGenCode.cpp codes/Acid.cpp)

add_executable(ClionProject ${SOURCE_FILES})