add_library(
    qni.core SHARED qni.cc qni-connector.cc
)

target_link_libraries(
    qni.core qni.api
)
