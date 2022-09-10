#include "socket_os_impl.hh"

#include <unistd.h>

#include "csockpp/exception.hh"


namespace csockpp {
namespace linux_ {

namespace socket_os_impl_internal {

int CreateDescriptor(
    AddressFamily af,
    Type type,
    Protocol protocol
) {
  auto descriptor = socket(
      static_cast<int>(af),
      static_cast<int>(type),
      static_cast<int>(protocol)
  );
  if(descriptor != -1) {
    return descriptor;
  }
  throw SocketOpenException();
}

}

SocketOsImpl::SocketOsImpl(int descriptor) noexcept 
    : SocketImpl(descriptor)
{}

SocketOsImpl::SocketOsImpl(
    AddressFamily af,
    Type type,
    Protocol protocol
) 
    : SocketOsImpl(socket_os_impl_internal::CreateDescriptor(af, type, protocol))
{}

SocketImpl* SocketOsImpl::clone() const noexcept {
  return new SocketOsImpl(descriptor);
}

bool SocketOsImpl::CloseImpl() noexcept {
  return close(descriptor) == 0;
}

bool SocketOsImpl::BindImpl(const Address& address) noexcept {
  return bind(descriptor, &address.addr, address.size) == 0;
}

bool SocketOsImpl::ListenImpl(const int& backlog) noexcept {
  return listen(descriptor, backlog) == 0;
}

}
}
