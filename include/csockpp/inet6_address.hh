#ifndef CSOCKPP_INET6_ADDRESS_HH__
#define CSOCKPP_INET6_ADDRESS_HH__

#include <netinet/in.h>

#include <string>

#include "inet_address.hh"


namespace csockpp {

class Inet6Address : public InetAddress {
public:
  Inet6Address(const struct sockaddr_in6& addr) noexcept;
  Inet6Address(
      const std::string& ip, 
      const uint16_t& port,
      uint32_t flowinfo = 0,
      uint32_t scope_id = 0
  );

public:
  uint16_t port() const noexcept override;
  void port(const uint16_t& value) noexcept override;
  std::string ip() const noexcept override;
  void ip(const std::string& value) override;

  uint32_t flowinfo() const noexcept;
  void flowinfo(uint32_t value) noexcept;
  uint32_t scope_id() const noexcept;
  void scope_id(uint32_t value) noexcept;
  
  std::string str() const noexcept override;

public:
  bool operator==(const sockaddr_in6& addr) const noexcept;

private:
  struct sockaddr_in6& addr_in_;
 
};

}


#endif
