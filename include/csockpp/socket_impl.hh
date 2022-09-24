#ifndef CSOCKPP_LINUX_SOCKET_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_IMPL_HH__

#include <set>

#include "address.hh"
#include "flag.hh"
#include "isocket.hh"


namespace csockpp {

class SocketImpl : public ISocket {
public:
  const int descriptor;

public:
  SocketImpl(int descriptor) noexcept;

public:
  SocketImpl* clone() const noexcept;

public:
  void Shutdown() const override;
  void Shutdown(Flag::Shut how) const override;
  void Close() const override;
  void Bind(const Address& address) const override;
  void Listen(const uint32_t& backlog) const override;
  void Connect(const Address& address) const override;
  Socket Accept(const std::set<Flag::Sock>& flags = {}) const override;
  Socket Accept(
      Address& address, 
      const std::set<Flag::Sock>& flags = {}
  ) const override;
  size_t Send(
      const void* buffer,
      const size_t& buffer_len, 
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t Recv(
      void* buffer,
      const size_t& buffer_len, 
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t SendTo(
      const void* buffer,
      const size_t& buffer_len, 
      const Address& address,
      const std::set<Flag::Msg>& flags = {}
  ) const override;
  size_t RecvFrom(
      void* buffer,
      const size_t& buffer_len,
      Address& address,
      const std::set<Flag::Msg>& flags = {}
  ) const override;

private:
  virtual SocketImpl* CloneImpl(int descriptor) const noexcept = 0;
  virtual bool ShutdownImpl(
      const int& descriptor, 
      const int& how
  ) const noexcept = 0;
  virtual bool CloseImpl(const int& descriptor) const noexcept = 0;
  virtual bool BindImpl(
      const int& descriptor,
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept = 0;
  virtual bool ListenImpl(
      const int& descriptor, 
      const int& backlog
  ) const noexcept = 0;
  virtual int ConnectImpl(
      const int& descriptor, 
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept = 0;
  virtual int AcceptImpl(
      const int& descriptor, 
      struct sockaddr* addr, 
      socklen_t* addr_len,
      const int& flags
  ) const noexcept = 0;
  virtual ssize_t SendImpl(
      const int& descriptor, 
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags
  ) const noexcept = 0;
  virtual ssize_t RecvImpl(
      const int& descriptor, 
      void* buffer,
      const size_t& buffer_len, 
      const int& flags
  ) const noexcept = 0;
  virtual ssize_t SendToImpl(
      const int& descriptor, 
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags,
      const struct sockaddr* addr,
      const socklen_t& addr_len
  ) const noexcept = 0;
  virtual ssize_t RecvFromImpl(
      const int& descriptor, 
      void* buffer,
      const size_t& buffer_len,
      const int& flags,
      sockaddr* addr,
      socklen_t* addr_len
  ) const noexcept = 0;
  
};

}


#endif
