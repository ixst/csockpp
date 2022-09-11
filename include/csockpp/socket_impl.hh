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
  virtual SocketImpl* clone() const noexcept = 0;

public:
  void Close() override;
  void Bind(const Address& address) override;
  void Listen(const int& backlog) override;
  void Connect(const Address& address) override;
  Socket Accept(Address& address, const std::set<Flag>& flags = {}) override;

private:
  virtual bool CloseImpl() noexcept = 0;
  virtual bool BindImpl(const Address& address) noexcept = 0;
  virtual bool ListenImpl(const int& backlog) noexcept = 0;
  virtual int ConnectImpl(const Address& address) noexcept = 0;
  virtual int AcceptImpl(
      Address& address, 
      const std::set<Flag>& flags = {}
  ) noexcept = 0;
  
};

}


#endif
