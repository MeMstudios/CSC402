cmake_minimum_required(VERSION 3.6)
project(hospitalCmd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp Patient.cpp Patient.h patients.txt Logger.cpp)
add_executable(hospitalCmd ${SOURCE_FILES})