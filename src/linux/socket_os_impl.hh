#ifndef CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_OS_IMPL_HH__

#include <set>

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
      const AddressFamily& af,
      const Type& type,
      const Protocol& protocol,
      const std::set<Flag::Sock>& flags = {}
  );

public:
  SocketImpl* clone() const noexcept;

private:
  bool CloseImpl() noexcept override;
  bool BindImpl(const Address& address) noexcept override;
  bool ListenImpl(const int& backlog) noexcept override;
  int ConnectImpl(const Address& address) noexcept override;
  int AcceptImpl(
      Address& address, 
      const std::set<Flag::Sock>& flags = {}
  ) noexcept override;
  ssize_t SendImpl(
      const void* buffer,
      const size_t& size, 
      const std::set<Flag::Msg>& flags = {}
  ) noexcept override;
  
};

}
}


#endif
