#ifndef CSOCKPP_SOCKET_HH__
#define CSOCKPP_SOCKET_HH__

#include <set>

#include "address_family.hh"
#include "type.hh"
#include "protocol.hh"
#include "flag.hh"
#include "address.hh"
#include "isocket.hh"


namespace csockpp {

class SocketImpl;

class Socket : public ISocket {
public:
  const int& descriptor;

  static const int kMaxConn;

public:
  Socket(SocketImpl* impl) noexcept;
  Socket(
      const AddressFamily& af,
      const Type& type,
      const Protocol& protocol,
      const std::set<Flag::Sock>& flags = {}
  );
  Socket(int descriptor) noexcept;
  Socket(const Socket& socket) noexcept;
  Socket(Socket&& socket) noexcept;
  ~Socket() noexcept override;

public:
  void Close() override;
  void Bind(const Address& address) override;
  void Listen(const int& backlog = kMaxConn) override;
  void Connect(const Address& address) override;
  Socket Accept(
      Address& address, 
      const std::set<Flag::Sock>& flags = {}
  ) override;
  size_t Send(
      const void* buffer, 
      const size_t& size,
      const std::set<Flag::Msg>& flags = {}
  );

private:
  SocketImpl* impl_;

};

}


#endif
