#ifndef CSOCKPP_ADDRESS_FAMILY_HH_
#define CSOCKPP_ADDRESS_FAMILY_HH_


#if defined(__linux__)
#include "linux/address_family.hh"
namespace csockpp {
using AddressFamily = linux_::AddressFamily;
}
#elif defined(BSD)
#include "bsd/address_family.hh"
namespace csockpp {
using AddressFamily = bsd::AddressFamily;
}
#elif defined(_WIN32)
#include "windows/address_family.hh"
namespace csockpp {
using AddressFamily = windows::AddressFamily;
}
#endif


#endif
