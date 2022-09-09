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

class IpParseException : public SystemException {};

}


#endif
