file(GLOB_RECURSE TCP_CLIENT_SOCKET_SOURCE tcp_client_socket.cc)

add_executable(tcp_client_socket ${TCP_CLIENT_SOCKET_SOURCE})

target_link_libraries(tcp_client_socket csockpp)
