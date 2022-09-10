#ifndef CSOCKPP_ISOCKET_HH__
#define CSOCKPP_ISOCKET_HH__

#include "address.hh"


namespace csockpp {

class ISocket {
public:
  virtual ~ISocket() noexcept {};

public:
  virtual void Close() = 0;
  virtual void Bind(const Address& address) = 0;

};

}


#endif
