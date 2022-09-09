#include "csockpp/inet4_address.hh"

#include <arpa/inet.h>

#include <cstring>
#include <sstream>

#include "csockpp/exception.hh"


namespace csockpp {

namespace inet4_address_internal {

struct sockaddr_in CreateSockAddr(
    const std::string& ip, 
    const uint16_t& port
) {
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if(!inet_pton(AF_INET, ip.data(), &addr.sin_addr)) {
    throw IpParseException();
  }
  return addr;
}

}



Inet4Address::Inet4Address(const struct sockaddr_in& addr) noexcept
    : InetAddress(&addr, sizeof(addr)),
      addr_in_((struct sockaddr_in&)(*data_))
{}

Inet4Address::Inet4Address(const std::string& ip, const uint16_t& port)
    : Inet4Address(inet4_address_internal::CreateSockAddr(ip, port))
{}

uint16_t Inet4Address::port() const noexcept {
  return ntohs(addr_in_.sin_port);
}

void Inet4Address::port(const uint16_t& value) noexcept {
  addr_in_.sin_port = htons(value);
}

std::string Inet4Address::ip() const noexcept {
  char buffer[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &addr_in_.sin_addr, buffer, INET_ADDRSTRLEN);
  return buffer;
}

void Inet4Address::ip(const std::string& value) {
  if(!inet_pton(AF_INET, value.c_str(), &addr_in_.sin_addr)) {
    throw IpParseException();
  }
}

std::string Inet4Address::str() const noexcept {
  std::stringstream sout;
  sout << ip() << ':' << port();
  return sout.str();
}

bool Inet4Address::operator==(const struct sockaddr_in& addr) const noexcept {
  return std::memcmp(&addr_in_, &data_, sizeof(addr));
}

}
