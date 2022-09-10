#include "csockpp/socket_impl.hh"

#include "csockpp/exception.hh"


namespace csockpp {

SocketImpl::SocketImpl(int descriptor) noexcept 
    : descriptor(descriptor)
{}

void SocketImpl::Close() {
  if(!CloseImpl()) {
    throw SocketCloseException();
  }
}

void SocketImpl::Bind(const Address& address) {
  if(!BindImpl(address)) {
    throw SocketBindException();
  }
}

}
