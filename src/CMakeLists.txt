add_library(
    qni.core SHARED qni.cc qni-connector.cc
)

target_link_libraries(
    qni.core qni.api
)

target_include_directories(
    qni.core PUBLIC
    ${CMAKE_BINARY_DIR})

install(
    TARGETS qni.core
    LIBRARY
        DESTINATION lib
        COMPONENT Libraries
        NAMELINK_COMPONENT Development
        )
