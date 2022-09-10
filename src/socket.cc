#include "csockpp/socket.hh"

#include <utility>
#include <limits>

#include "csockpp/socket_impl.hh"
#include "socket_os_impl.hh"


namespace csockpp {

const int Socket::kMaxConn = 
#ifndef SOMAXCONN
    SOMAXCONN
#else
    std::numeric_limits<int>::max();
#endif

Socket::Socket(SocketImpl* impl) noexcept 
    : descriptor(impl->descriptor),
      impl_(impl)
{}

Socket::Socket(
    AddressFamily af,
    Type type,
    Protocol protocol
) 
    : Socket(new SocketOsImpl(af, type, protocol))
{}

Socket::Socket(int descriptor) noexcept
    : Socket(new SocketOsImpl(descriptor))
{}

Socket::Socket(const Socket& socket) noexcept 
    : Socket(socket.impl_->clone())
{}

Socket::Socket(Socket&& socket) noexcept 
    : Socket(socket.impl_)
{
  socket.impl_ = nullptr;
}

Socket::~Socket() noexcept {
  delete impl_;
}

void Socket::Close() {
  impl_->Close();
}

void Socket::Bind(const Address& address) {
  impl_->Bind(address);
}

void Socket::Listen(const int& backlog) {
  impl_->Listen(backlog);
}

bool Socket::Connect(const Address& address) {
  return impl_->Connect(address);
}

}
