set(
    EXAMPLES
    tcp_client_socket
    tcp_echo
)

foreach(example ${EXAMPLES})
  add_executable(${example} ${example}.cc)
  target_link_libraries(${example} csockpp)
endforeach()

