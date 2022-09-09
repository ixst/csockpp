#include "csockpp/exception.hh"

#include <errno.h>
#include <string.h>


namespace csockpp {

SocketException::SocketException(int error) noexcept 
    : error(error)
{}

SocketException::SocketException() noexcept 
    : SocketException(errno)
{}

const char* SocketException::what() const noexcept {
  return strerror(error);
}

}
