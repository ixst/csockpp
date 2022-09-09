#include "csockpp/inet_address.hh"


namespace csockpp {


InetAddress::InetAddress(const void* addr, decltype(sizeof(0)) size) noexcept 
    : Address(addr, size)
{}

std::ostream& operator<<(
    std::ostream& os, 
    const InetAddress& address
) noexcept {
  os << address.str();
  return os;
}

}
