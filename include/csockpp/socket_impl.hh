#ifndef CSOCKPP_LINUX_SOCKET_IMPL_HH__
#define CSOCKPP_LINUX_SOCKET_IMPL_HH__

#include "isocket.hh"


namespace csockpp {

class SocketImpl : public ISocket {
public:
  const int descriptor;

public:
  SocketImpl(int descriptor) noexcept;

public:
  void Close() override;

private:
  virtual bool CloseImpl() noexcept = 0;
  
};

}


#endif
