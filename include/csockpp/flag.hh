#ifndef CSOCKPP_FLAG_HH_
#define CSOCKPP_FLAG_HH_


#if defined(__linux__)
#include "linux/flag.hh"
namespace csockpp {
using Flag = linux_::Flag;
}
#elif defined(BSD)
#include "bsd/flag.hh"
namespace csockpp {
using Flag = bsd::Flag;
}
#elif defined(_WIN32)
#include "windows/flag.hh"
namespace csockpp {
using Flag = windows::Flag;
}
#endif


#endif
