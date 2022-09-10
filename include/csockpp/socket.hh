#ifndef CSOCKPP_SOCKET_HH__
#define CSOCKPP_SOCKET_HH__

#include "address_family.hh"
#include "type.hh"
#include "protocol.hh"
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
      AddressFamily af,
      Type type,
      Protocol protocol
  );
  Socket(int descriptor) noexcept;
  Socket(const Socket& socket) noexcept;
  Socket(Socket&& socket) noexcept;
  ~Socket() noexcept override;

public:
  void Close() override;
  void Bind(const Address& address) override;
  void Listen(const int& backlog = kMaxConn) override;

private:
  SocketImpl* impl_;

};

}


#endif
