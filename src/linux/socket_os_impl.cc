#include "socket_os_impl.hh"

#include <unistd.h>

#include "csockpp/exception.hh"


namespace csockpp {
namespace linux_ {

namespace socket_os_impl_internal {

int CreateDescriptor(
    const int& address_family,
    const int& type,
    const int& protocol
) {
  auto descriptor = socket(address_family, type, protocol);
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
    const int& address_family,
    const int& type,
    const int& protocol
) 
    : SocketOsImpl(
          socket_os_impl_internal::CreateDescriptor(
              address_family, 
              type, 
              protocol
          )
      )
{}

SocketImpl* SocketOsImpl::CloneImpl(int descriptor) const noexcept {
  return new SocketOsImpl(descriptor);
}

bool SocketOsImpl::CloseImpl(const int& descriptor) const noexcept {
  return close(descriptor) == 0;
}

bool SocketOsImpl::BindImpl(
    const int& descriptor, 
    const struct sockaddr* addr, 
    const socklen_t& addr_len
) const noexcept {
  return bind(descriptor, addr, addr_len) == 0;
}

bool SocketOsImpl::ListenImpl(
    const int& descriptor, 
    const int& backlog
) const noexcept {
  return listen(descriptor, backlog) == 0;
}

int SocketOsImpl::ConnectImpl(
    const int& descriptor, 
    const struct sockaddr* addr, 
    const socklen_t& addr_len
) const noexcept {
  if (connect(descriptor, addr, addr_len) == 0) {
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
    const int& descriptor, 
    struct sockaddr* addr, 
    socklen_t* addr_len,
    const int& flags
) const noexcept {
  if (accept4(descriptor, addr, addr_len, flags) == 0) {
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

ssize_t SocketOsImpl::SendImpl(
    const int& descriptor, 
    const void* buffer, 
    const size_t& buffer_len,
    const int& flags
) const noexcept {
  auto sent_size = send(descriptor, buffer, buffer_len, flags);
  if (sent_size != -1) {
    return sent_size;
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

ssize_t SocketOsImpl::RecvImpl(
    const int& descriptor, 
    void* buffer, 
    const size_t& buffer_len,
    const int& flags
) const noexcept {
  auto recv_size = recv(descriptor, buffer, buffer_len, flags);
  if (recv_size != -1) {
    return recv_size;
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

ssize_t SocketOsImpl::SendToImpl(
    const int& descriptor, 
    const void* buffer,
    const size_t& buffer_len, 
    const int& flags,
    const struct sockaddr* addr,
    const socklen_t& addr_len
) const noexcept {
  auto sent_size = sendto(
      descriptor, 
      buffer, 
      buffer_len, 
      flags,
      addr, 
      addr_len
  );
  if (sent_size != -1) {
    return sent_size;
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
