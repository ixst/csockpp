#include "csockpp/socket_impl.hh"

#include "csockpp/exception.hh"
#include "csockpp/socket.hh"


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

void SocketImpl::Connect(const Address& address) {
  switch (ConnectImpl(address)) {
    case -1: throw SocketConnectException();
    case -2: throw SocketNonblockingException();
  }
}

Socket SocketImpl::Accept(
    Address& address, 
    const std::set<Flag::Sock>& flags
) {
  auto descriptor = AcceptImpl(address, flags);
  switch (descriptor) {
    case -1: throw SocketConnectException();
    case -2: throw SocketNonblockingException();
    default: return Socket(descriptor);
  }
}

size_t SocketImpl::Send(
    const void* buffer, 
    const size_t& size, 
    const std::set<Flag::Msg>& flags
) {
  auto sent_size = SendImpl(buffer, size, flags);
  switch (sent_size) {
    case -1: throw SocketSendException();
    case -2: throw SocketNonblockingException();
    default: return static_cast<size_t>(sent_size);
  }
}

}
