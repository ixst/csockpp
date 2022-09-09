#ifndef CSOCKPP_EXCEPTION_HH__
#define CSOCKPP_EXCEPTION_HH__

#include <exception>


namespace csockpp {

class SocketException : public std::exception {
public:
  int error;

public:
  SocketException() noexcept;

public:
  const char* what() const noexcept override;

};

class SocketOpenException : public SocketException {};

class SocketCloseException : public SocketException {};

}


#endif
