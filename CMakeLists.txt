project(qni.core)

cmake_minimum_required(VERSION 3.1.2)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "([Cc]lang|GNU)")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
endif()

add_subdirectory(api)
include_directories(include)
add_subdirectory(include)
add_subdirectory(src)
