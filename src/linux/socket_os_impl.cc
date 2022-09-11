#include "socket_os_impl.hh"

#include <unistd.h>

#include "csockpp/exception.hh"


namespace csockpp {
namespace linux_ {

namespace socket_os_impl_internal {

int CreateDescriptor(
    const AddressFamily& address_family,
    const Type& type,
    const Protocol& protocol,
    const std::set<Flag>& flags
) {
  int itype = static_cast<int>(type);
  for (const auto& flag : flags) {
    itype |= static_cast<int>(flag);
  }

  auto descriptor = socket(
      static_cast<int>(address_family),
      itype,
      static_cast<int>(protocol)
  );
  if (descriptor != -1) {
    return descriptor;
  }
  throw SocketOpenException();
}

}

SocketOsImpl::SocketOsImpl(int descriptor) noexcept 
    : SocketImpl(descriptor)
{}

SocketOsImpl::SocketOsImpl(
    const AddressFamily& address_family,
    const Type& type,
    const Protocol& protocol,
    const std::set<Flag>& flags
) 
    : SocketOsImpl(
          socket_os_impl_internal::CreateDescriptor(
              address_family, 
              type, 
              protocol,
              flags
          )
      )
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

int SocketOsImpl::ConnectImpl(const Address& address) noexcept {
  if (connect(descriptor, &address.addr, address.size) == 0) {
    return 0;
  } else if (
#ifdef EWOULDBLOCK
      errno == EWOULDBLOCK ||
#endif
#ifdef EAGAIN
      errno == EAGAIN ||
#endif
#ifdef EINPROGRESS
      errno == EINPROGRESS ||
#endif
      false
  ) {
    return -2;
  } else {
    return -1;
  }
}

int SocketOsImpl::AcceptImpl(
    Address& address, 
    const std::set<Flag>& flags
) noexcept {
  int iflags = 0;
  for (const auto& flag : flags) {
    iflags |= static_cast<int>(flag);
  }
 
  if (
      accept4(
          descriptor, 
          &address.addr, 
          const_cast<socklen_t*>(&address.size),
          iflags
      ) == 0
  ) {
    return 0;
  } else if (
#ifdef EWOULDBLOCK
      errno == EWOULDBLOCK ||
#endif
#ifdef EAGAIN
      errno == EAGAIN ||
#endif
      false
  ) {
    return -2;
  } else {
    return -1;
  }
}

}
}
