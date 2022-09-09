#include "csockpp/socket.hh"

#include "csockpp/socket_impl.hh"
#include "socket_os_impl.hh"


namespace csockpp {

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

Socket::~Socket() noexcept {
  delete impl_;
}

void Socket::Close() {
  impl_->Close();
}

}
