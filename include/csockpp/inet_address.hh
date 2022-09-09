#ifndef CSOCKPP_INET_ADDRESS_HH__
#define CSOCKPP_INET_ADDRESS_HH__

#include <iostream>
#include <string>

#include "address.hh"


namespace csockpp {

class InetAddress : public Address {
public:
  InetAddress(const void* addr, decltype(sizeof(0)) size) noexcept;

public:
  virtual uint16_t port() const noexcept = 0;
  virtual void port(const uint16_t& value) noexcept = 0;
  virtual std::string ip() const noexcept = 0;
  virtual void ip(const std::string& value) = 0;
  
  virtual std::string str() const noexcept = 0;
 
};

std::ostream& operator<<(
    std::ostream& os, 
    const InetAddress& address
) noexcept;

}


#endif
