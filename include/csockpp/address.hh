#ifndef CSOCKPP_ADDRESS_HH__
#define CSOCKPP_ADDRESS_HH__

#include <netinet/in.h>

#include "address_family.hh"


namespace csockpp {

class Address {
protected:
  uint8_t* data_;

public:
  socklen_t size;
  AddressFamily& family;
  struct sockaddr& addr;

public:
  Address(void* addr, decltype(sizeof(0)) size) noexcept;
  ~Address() noexcept;

public:
  bool operator==(const Address&) const noexcept;

};

}


#endif
