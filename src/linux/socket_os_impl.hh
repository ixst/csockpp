#ifndef CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__

#include "csockpp/address_family.hh"
#include "csockpp/type.hh"
#include "csockpp/protocol.hh"
#include "csockpp/address.hh"
#include "csockpp/socket_impl.hh"


namespace csockpp {
namespace linux_ {

class SocketOsImpl : public SocketImpl {
public:
  SocketOsImpl(int descriptor) noexcept;
  SocketOsImpl(
      AddressFamily af,
      Type type,
      Protocol protocol
  );

public:
  SocketImpl* clone() const noexcept;

private:
  bool CloseImpl() noexcept override;
  bool BindImpl(const Address& address) noexcept override;
  bool ListenImpl(const int& backlog) noexcept override;
  int ConnectImpl(const Address& address) noexcept override;
  
};

}
}


#endif
