cmake_minimum_required(VERSION 3.12)
project(qni.core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(include)
add_subdirectory(include)
add_subdirectory(qni-api)
add_subdirectory(src)
