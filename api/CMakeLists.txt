set(API_SOURCE
    ${CMAKE_SOURCE_DIR}/include/api/qni-api.pb.cc)

set(API_HEADER
    ${CMAKE_SOURCE_DIR}/include/api/qni-api.pb.h)

add_custom_command(
    OUTPUT ${API_SOURCE} ${API_HEADER}
    COMMAND protoc
    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/protos --cpp_out=${CMAKE_SOURCE_DIR}/include/api qni-api.proto
)

add_library(qni.api STATIC
    ${API_SOURCE} ${API_HEADER})

target_link_libraries(
    qni.api ${Protobuf_LIBRARIES}
)

target_include_directories(
	qni.api PUBLIC
	${Protobuf_INCLUDE_DIR}
)
