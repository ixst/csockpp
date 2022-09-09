#ifndef CSOCKPP_ADDRESS_HH__
#define CSOCKPP_ADDRESS_HH__

#include <netinet/in.h>

#include "address_family.hh"


namespace csockpp {

class Address {
public:
  socklen_t size;
  const AddressFamily& family;

public:
  Address(void* addr, decltype(sizeof(0)) size) noexcept;
  ~Address() noexcept;

public:
  sockaddr* const operator&() const noexcept;

private:
  uint8_t* buffer_;

};

}


#endif
