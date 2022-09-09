if(CMAKE_BUILD_TYPE STREQUAL Coverage) 
  add_compile_options(--coverage)
endif()

file(GLOB_RECURSE SOURCES *.cc)

add_library(csockpp SHARED ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL Coverage)
  target_link_libraries(csockpp gcov)
endif()
