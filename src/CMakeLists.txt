add_library(
    qni.core SHARED

    qni-console.cpp
    qni-hub.cpp
    qni-connector.cpp
    qni-extern.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_link_libraries(
		qni.core
		qni.api
		${Protobuf_LIBRARIES}
	)
else ()
	target_link_libraries(
		qni.core
		qni.api
		${Protobuf_LIBRARIES}
		pthread
	)
endif ()

target_include_directories(
    qni.core PUBLIC
	${Protobuf_INCLUDE_DIR}
)


if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	install(
		TARGETS qni.core
		DESTINATION bin
	)
else()
	install(
		TARGETS qni.core
		DESTINATION lib
	)
endif()
