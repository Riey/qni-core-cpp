add_library(
    qni.core SHARED

    qni.cpp
    qni-connector.cpp
    qni-extern.cpp
    internal/qni-deleter.cpp
)

target_link_libraries(
    qni.core qni.api
)

target_include_directories(
    qni.core PUBLIC
    ${CMAKE_BINARY_DIR})

install(
    TARGETS qni.core
    LIBRARY DESTINATION lib
    )
