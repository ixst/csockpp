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

  static const uint32_t kMaxConn;

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
  void Close() const override;
  void Bind(const Address& address) const override;
  void Listen(const uint32_t& backlog = kMaxConn) const override;
  void Connect(const Address& address) const override;
  Socket Accept(
      Address& address, 
      const std::set<Flag::Sock>& flags = {}
  ) const override;
  size_t Send(
      const void* buffer, 
      const size_t& buffer_len,
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t Recv(
      void* buffer, 
      const size_t& buffer_len,
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t SendTo(
      const void* buffer, 
      const size_t& buffer_len,
      const Address& address,
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t RecvFrom(
      void* buffer,
      const size_t& buffer_len,
      Address& address,
      const std::set<Flag::Msg>& flags = {}
  ) const override;

private:
  SocketImpl* impl_;

};

}


#endif
