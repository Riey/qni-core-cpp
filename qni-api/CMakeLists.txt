find_package(Protobuf REQUIRED)

set(API_SOURCE
    ${CMAKE_CURRENT_BINARY_DIR}/qni-api.pb.cc)

set(API_HEADER
    ${CMAKE_CURRENT_BINARY_DIR}/qni-api.pb.h)

add_custom_command(
    OUTPUT ${API_SOURCE} ${API_HEADER}
    COMMAND protoc
    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/protos --cpp_out=${CMAKE_CURRENT_BINARY_DIR} qni-api.proto
)

add_library(qni.api STATIC
    ${API_SOURCE} ${API_HEADER})

target_link_libraries(
    qni.api protobuf
)

install(FILES ${API_HEADER} DESTINATION include/qni-api)
