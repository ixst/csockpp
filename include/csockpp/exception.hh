#ifndef CSOCKPP_EXCEPTION_HH__
#define CSOCKPP_EXCEPTION_HH__

#include <exception>


namespace csockpp {

class SystemException : public std::exception {
public:
  int error;

public:
  SystemException(int error) noexcept;
  SystemException() noexcept;

public:
  const char* what() const noexcept override;

};

class SocketException : public SystemException {};

class SocketOpenException : public SocketException {};

class SocketCloseException : public SocketException {};

class SocketBindException : public SocketException {};
class SocketListenException : public SocketException {};
class SocketConnectException : public SocketException {};
class SocketAcceptException : public SocketException {};
class SocketSendException : public SocketException {};
class SocketRecvException : public SocketException {};
class SocketNonblockingException : public SocketException {};

class IpParseException : public SystemException {};

}


#endif
