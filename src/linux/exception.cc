#include "csockpp/exception.hh"

#include <errno.h>
#include <string.h>


namespace csockpp {

SocketException::SocketException() noexcept 
    : error(errno)
{}

const char* SocketException::what() const noexcept {
  return strerror(error);
}

}
