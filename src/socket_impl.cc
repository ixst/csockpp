#include "csockpp/socket_impl.hh"

#include "csockpp/exception.hh"


namespace csockpp {

SocketImpl::SocketImpl(int descriptor) noexcept 
    : descriptor(descriptor)
{}

void SocketImpl::Close() {
  if (!CloseImpl()) {
    throw SocketCloseException();
  }
}

void SocketImpl::Bind(const Address& address) {
  if (!BindImpl(address)) {
    throw SocketBindException();
  }
}

void SocketImpl::Listen(const int& backlog) {
  if (!ListenImpl(backlog)) {
    throw SocketListenException();
  }
}

bool SocketImpl::Connect(const Address& address) {
  auto result = ConnectImpl(address);
  if (result == 0) {
    return true;
  } else if(result == 1) {
    return false;
  } else {
    throw SocketConnectException();
  }
}

}
