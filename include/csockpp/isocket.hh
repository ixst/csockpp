#ifndef CSOCKPP_ISOCKET_HH__
#define CSOCKPP_ISOCKET_HH__


namespace csockpp {

class ISocket {
public:
  virtual ~ISocket() noexcept {};

public:
  virtual void Close() = 0;

};

}


#endif
