file(GLOB_RECURSE SOURCES *.cc)

add_executable(example ${SOURCES})

target_link_libraries(example csockpp)
