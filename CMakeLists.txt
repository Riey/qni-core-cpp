cmake_minimum_required(VERSION 3.12)
project(qni.core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_subdirectory(qni-api)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/qni-api
    include)
add_subdirectory(src)
