add_library(
    qni.core SHARED

    qni-console.cpp
    qni-hub.cpp
    qni-connector.cpp
    qni-extern.cpp
)

target_link_libraries(
    qni.core
    qni.api
    protobuf
    pthread
)

target_include_directories(
    qni.core PUBLIC
    ${CMAKE_BINARY_DIR}
)

install(
    TARGETS qni.core
    LIBRARY DESTINATION lib
    )
