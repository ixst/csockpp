#ifndef CSOCKPP_PROTOCOL_HH__
#define CSOCKPP_PROTOCOL_HH__


#if defined(__linux__)
#include "linux/protocol.hh"
namespace csockpp {
using Protocol = linux_::Protocol;
}
#elif defined(BSD)
#include "bsd/protocol.hh"
namespace csockpp {
using Protocol = bsd::Protocol;
}
#elif defined(_WIN32)
#include "windows/protocol.hh"
namespace csockpp {
using Protocol = windows::Protocol;
}
#endif


#endif
