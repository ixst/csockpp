#ifndef CSOCKPP_ISOCKET_HH__
#define CSOCKPP_ISOCKET_HH__

#include <set>

#include "address.hh"
#include "flag.hh"


namespace csockpp {

class Socket;

class ISocket {
public:
  virtual ~ISocket() noexcept {};

public:
  virtual void Close() = 0;
  virtual void Bind(const Address& address) = 0;
  virtual void Listen(const int& backlog) = 0;
  virtual void Connect(const Address& address) = 0;
  virtual Socket Accept(
      Address& address, 
      const std::set<Flag>& flags = {}
  ) = 0;

};

}


#endif
