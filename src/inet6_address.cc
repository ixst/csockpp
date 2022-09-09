#include "csockpp/inet6_address.hh"

#include <arpa/inet.h>

#include <cstring>
#include <sstream>

#include "csockpp/exception.hh"


namespace csockpp {

namespace inet6_address_internal {

struct sockaddr_in6 CreateSockAddr(
    const std::string& ip, 
    const uint16_t& port,
    uint32_t flowinfo,
    uint32_t scope_id
) {
  struct sockaddr_in6 addr = {};
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(port);
  addr.sin6_flowinfo = flowinfo;
  addr.sin6_scope_id = scope_id;
  if(!inet_pton(AF_INET6, ip.data(), &addr.sin6_addr)) {
    throw IpParseException();
  }
  return addr;
}

}



Inet6Address::Inet6Address(const struct sockaddr_in6& addr) noexcept
    : InetAddress(&addr, sizeof(addr)),
      addr_in_((struct sockaddr_in6&)(*data_))
{}

Inet6Address::Inet6Address(
    const std::string& ip, 
    const uint16_t& port,
    uint32_t flowinfo,
    uint32_t scope_id
)
    : Inet6Address(
          inet6_address_internal::CreateSockAddr(
              ip, 
              port,
              flowinfo,
              scope_id
          )
      )
{}

uint16_t Inet6Address::port() const noexcept {
  return ntohs(addr_in_.sin6_port);
}

void Inet6Address::port(const uint16_t& value) noexcept {
  addr_in_.sin6_port = htons(value);
}

std::string Inet6Address::ip() const noexcept {
  char buffer[INET_ADDRSTRLEN];
  inet_ntop(AF_INET6, &addr_in_.sin6_addr, buffer, INET6_ADDRSTRLEN);
  return buffer;
}

void Inet6Address::ip(const std::string& value) {
  if(!inet_pton(AF_INET6, value.c_str(), &addr_in_.sin6_addr)) {
    throw IpParseException();
  }
}

uint32_t Inet6Address::flowinfo() const noexcept {
  return addr_in_.sin6_flowinfo;
}

void Inet6Address::flowinfo(uint32_t value) noexcept {
  addr_in_.sin6_flowinfo = value;
}

uint32_t Inet6Address::scope_id() const noexcept {
  return addr_in_.sin6_scope_id;
}

void Inet6Address::scope_id(uint32_t value) noexcept {
  addr_in_.sin6_scope_id = value;
}

std::string Inet6Address::str() const noexcept {
  std::stringstream sout;
  sout << '[' << ip() << "]:" << port();
  return sout.str();
}

bool Inet6Address::operator==(const sockaddr_in6& addr) const noexcept {
  return std::memcmp(&addr_in_, &data_, sizeof(addr));
}

}
