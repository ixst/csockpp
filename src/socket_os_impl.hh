#ifndef CSOCKPP_SOCKET_OS_IMPL_HH__
#define CSOCKPP_SOCKET_OS_IMPL_HH__


#if defined(__linux__)
#include "linux/socket_os_impl.hh"
namespace csockpp {
using SocketOsImpl = linux_::SocketOsImpl;
}
#elif defined(BSD)
#include "bsd/socket_os_impl.hh"
namespace csockpp {
using SocketOsImpl = bsd::SocketOsImpl;
}
#elif defined(_WIN32)
#include "windows/socket_os_impl.hh"
namespace csockpp {
using SocketOsImpl = windows::SocketOsImpl;
}
#endif


#endif
