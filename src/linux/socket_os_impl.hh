#ifndef CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__

#include "csockpp/address_family.hh"
#include "csockpp/type.hh"
#include "csockpp/protocol.hh"
#include "csockpp/socket_impl.hh"


namespace csockpp {
namespace linux_ {

class SocketOsImpl : public SocketImpl {
public:
  SocketOsImpl(
      AddressFamily af,
      Type type,
      Protocol protocol
  );

private:
  bool CloseImpl() noexcept override;
  
};

}
}


#endif
