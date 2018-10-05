cmake_minimum_required(VERSION 3.12)
project(qni.core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -fpic")

include_directories(include)
add_subdirectory(include)
add_subdirectory(qni-api)
add_subdirectory(src)
