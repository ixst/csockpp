#include "csockpp/socket.hh"

#include <utility>
#include <limits>

#include "csockpp/socket_impl.hh"
#include "socket_os_impl.hh"


namespace csockpp {

namespace socket_internal {

int CalcType(const Type& type, const std::set<Flag::Sock>& flags) noexcept {
  int ret = static_cast<int>(type);
  for (const auto& flag : flags) {
    ret |= static_cast<int>(flag);
  }
  return ret;
}

}

const uint32_t Socket::kMaxConn = 
#ifdef SOMAXCONN
    static_cast<uint32_t>(SOMAXCONN);
#else
    static_cast<uint32_t>(std::numeric_limits<int>::max());
#endif

Socket::Socket(SocketImpl* impl) noexcept 
    : descriptor(impl->descriptor),
      impl_(impl)
{}

Socket::Socket(
    const AddressFamily& af,
    const Type& type,
    const Protocol& protocol,
    const std::set<Flag::Sock>& flags
) 
    : Socket(
          new SocketOsImpl(
              static_cast<int>(af), 
              socket_internal::CalcType(type, flags), 
              static_cast<int>(protocol)
          )
      )
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

void Socket::Shutdown() const {
  impl_->Shutdown();
}

void Socket::Shutdown(Flag::Shut how) const {
  impl_->Shutdown(how);
}

void Socket::Close() const {
  impl_->Close();
}

void Socket::Bind(const Address& address) const {
  impl_->Bind(address);
}

void Socket::Listen(const uint32_t& backlog) const {
  impl_->Listen(backlog);
}

void Socket::Connect(const Address& address) const {
  return impl_->Connect(address);
}

Socket Socket::Accept(
    Address& address, 
    const std::set<Flag::Sock>& flags
) const {
  return impl_->Accept(address, flags);
}

size_t Socket::Send(
    const void* buffer, 
    const size_t& buffer_len,
    const std::set<Flag::Msg>& flags
) const {
  return impl_->Send(buffer, buffer_len, flags);
}

size_t Socket::Recv(
    void* buffer, 
    const size_t& buffer_len,
    const std::set<Flag::Msg>& flags
) const {
  return impl_->Recv(buffer, buffer_len, flags);
}

size_t Socket::SendTo(
    const void* buffer, 
    const size_t& buffer_len,
    const Address& address,
    const std::set<Flag::Msg>& flags
) const {
  return impl_->SendTo(buffer, buffer_len, address, flags);
}

size_t Socket::RecvFrom(
    void* buffer,
    const size_t& buffer_len,
    Address& address,
    const std::set<Flag::Msg>& flags
) const {
  return impl_->RecvFrom(buffer, buffer_len, address, flags);
}

}
