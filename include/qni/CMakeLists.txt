file(GLOB HeaderFiles "*.hpp")
install(FILES ${HeaderFiles} DESTINATION include/qni)

add_subdirectory(api)
