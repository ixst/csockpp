#ifndef CSOCKPP_TYPE_HH__
#define CSOCKPP_TYPE_HH__


#if defined(__linux__)
#include "linux/type.hh"
namespace csockpp {
using Type = linux_::Type;
}
#elif defined(BSD)
#include "bsd/type.hh"
namespace csockpp {
using Type = bsd::Type;
}
#elif defined(_WIN32)
#include "windows/type.hh"
namespace csockpp {
using Type = windows::Type;
}
#endif


#endif
