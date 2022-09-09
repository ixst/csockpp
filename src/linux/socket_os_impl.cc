#include "socket_os_impl.hh"

#include <unistd.h>
#include <errno.h>

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

SocketOsImpl::SocketOsImpl(
    AddressFamily af,
    Type type,
    Protocol protocol
) 
    : SocketImpl(socket_os_impl_internal::CreateDescriptor(af, type, protocol))
{}

bool SocketOsImpl::CloseImpl() noexcept {
  return close(descriptor) != -1;
}

}
}
