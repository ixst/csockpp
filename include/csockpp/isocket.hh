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
  virtual void Close() const = 0;
  virtual void Bind(const Address& address) const = 0;
  virtual void Listen(const uint32_t& backlog) const = 0;
  virtual void Connect(const Address& address) const = 0;
  virtual Socket Accept(
      Address& address, 
      const std::set<Flag::Sock>& flags = {}
  ) const = 0;
  virtual size_t Send(
      const void* buffer, 
      const size_t& buffer_len, 
      const std::set<Flag::Msg>& flags = {}
  ) const = 0;
  virtual size_t Recv(
      void* buffer, 
      const size_t& buffer_len, 
      const std::set<Flag::Msg>& flags = {}
  ) const = 0;
  virtual size_t SendTo(
      const void* buffer, 
      const size_t& buffer_len, 
      const Address& address,
      const std::set<Flag::Msg>& flags = {}
  ) const = 0;

};

}


#endif
