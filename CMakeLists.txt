project(qni.core)

cmake_minimum_required(VERSION 3.8)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	include("$ENV{VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /EHsc")
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
endif()

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(api)
include_directories(include)
add_subdirectory(include)
add_subdirectory(src)
