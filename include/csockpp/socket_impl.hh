#ifndef CSOCKPP_LINUX_SOCKET_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_IMPL_HH__

#include "address.hh"
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

private:
  virtual bool CloseImpl() noexcept = 0;
  virtual bool BindImpl(const Address& address) noexcept = 0;
  
};

}


#endif
