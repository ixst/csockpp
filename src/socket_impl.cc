#include "csockpp/socket_impl.hh"

#include "csockpp/exception.hh"
#include "csockpp/socket.hh"


namespace csockpp {

namespace socket_impl_internal {

template <class T>
int CalcFlags(const std::set<T>& flags) noexcept {
  int ret = 0;
  for(const auto& flag : flags) {
    ret |= static_cast<int>(flag);
  }
  return ret;
}

}

SocketImpl::SocketImpl(int descriptor) noexcept 
    : descriptor(descriptor)
{}

SocketImpl* SocketImpl::clone() const noexcept {
  return CloneImpl(descriptor);
}

void SocketImpl::Close() const {
  if (!CloseImpl(descriptor)) {
    throw SocketCloseException();
  }
}

void SocketImpl::Bind(const Address& address) const {
  if (!BindImpl(descriptor, &address.addr, address.size)) {
    throw SocketBindException();
  }
}

void SocketImpl::Listen(const uint32_t& backlog) const {
  if (
      !ListenImpl(
          descriptor,
          backlog > Socket::kMaxConn 
              ? static_cast<int>(Socket::kMaxConn)
              : static_cast<int>(backlog)
      )
  ) {
    throw SocketListenException();
  }
}

void SocketImpl::Connect(const Address& address) const {
  switch (ConnectImpl(descriptor, &address.addr, address.size)) {
    case -1: throw SocketConnectException();
    case -2: throw SocketNonblockingException();
  }
}

Socket SocketImpl::Accept(
    Address& address, 
    const std::set<Flag::Sock>& flags
) const {
  auto accepted = AcceptImpl(
      descriptor,
      &address.addr, 
      const_cast<socklen_t*>(&address.size), 
      socket_impl_internal::CalcFlags(flags)    
  );
  switch (accepted) {
    case -1: throw SocketAcceptException();
    case -2: throw SocketNonblockingException();
    default: return Socket(accepted);
  }
}

size_t SocketImpl::Send(
    const void* buffer, 
    const size_t& buffer_len, 
    const std::set<Flag::Msg>& flags
) const {
  auto sent_size = SendImpl(
      descriptor,
      buffer, 
      buffer_len, 
      socket_impl_internal::CalcFlags(flags)
  );
  switch (sent_size) {
    case -1: throw SocketSendException();
    case -2: throw SocketNonblockingException();
    default: return static_cast<size_t>(sent_size);
  }
}

size_t SocketImpl::Recv(
    void* buffer, 
    const size_t& buffer_len, 
    const std::set<Flag::Msg>& flags
) const {
  auto recv_size = RecvImpl(
      descriptor,
      buffer, 
      buffer_len, 
      socket_impl_internal::CalcFlags(flags)
  );
  switch (recv_size) {
    case -1: throw SocketRecvException();
    case -2: throw SocketNonblockingException();
    default: return static_cast<size_t>(recv_size);
  }
}

}
