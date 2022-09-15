#ifndef CSOCKPP_INET4_ADDRESS_HH__
#define CSOCKPP_INET4_ADDRESS_HH__

#include <netinet/in.h>

#include <string>

#include "inet_address.hh"


namespace csockpp {

class Inet4Address : public InetAddress {
public:
  Inet4Address(const struct sockaddr_in& addr = {}) noexcept;
  Inet4Address(const std::string& ip, const uint16_t& port);

public:
  uint16_t port() const noexcept override;
  void port(const uint16_t& value) noexcept override;
  std::string ip() const noexcept override;
  void ip(const std::string& value) override;
  
  std::string str() const noexcept override;

private:
  struct sockaddr_in& addr_in_;
 
};

}


#endif
