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
  SocketOsImpl(const int& af, const int& type, const int& protocol);

private:
  SocketImpl* CloneImpl(int descriptor) const noexcept override;
  bool CloseImpl(const int& descriptor) const noexcept override;
  bool BindImpl(
      const int& descriptor, 
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept override;
  bool ListenImpl(
      const int& descriptor, 
      const int& backlog
  ) const noexcept override;
  int ConnectImpl(
      const int& descriptor, 
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept override;
  int AcceptImpl(
      const int& descriptor, 
      struct sockaddr* addr, 
      socklen_t* addr_len,
      const int& flags
  ) const noexcept override;
  ssize_t SendImpl(
      const int& descriptor, 
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags
  ) const noexcept override;
  ssize_t RecvImpl(
      const int& descriptor, 
      void* buffer,
      const size_t& buffer_len, 
      const int& flags 
  ) const noexcept override;
  ssize_t SendToImpl(
      const int& descriptor, 
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags,
      const struct sockaddr* addr,
      const socklen_t& addr_len
  ) const noexcept override;
  
};

}
}


#endif
