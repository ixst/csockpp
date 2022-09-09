file(GLOB_RECURSE SOURCES *.cc)

add_executable(test ${SOURCES})

target_link_libraries(test csockpp gtest)
