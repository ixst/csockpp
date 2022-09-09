#ifndef CSOCKPP_SOCKET_HH__
#define CSOCKPP_SOCKET_HH__

#include "address_family.hh"
#include "type.hh"
#include "protocol.hh"
#include "isocket.hh"


namespace csockpp {

class SocketImpl;

class Socket : public ISocket {
public:
  const int& descriptor;

public:
  Socket(SocketImpl* impl) noexcept;
  Socket(
      AddressFamily af,
      Type type,
      Protocol protocol
  );
  ~Socket() noexcept override;

public:
  void Close() override;

private:
  SocketImpl* impl_;

};

}


#endif
