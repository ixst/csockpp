#include "csockpp/exception.hh"

#include <cerrno>
#include <cstring>


namespace csockpp {

SystemException::SystemException(int error) noexcept 
    : error(error)
{}

SystemException::SystemException() noexcept 
    : SystemException(errno)
{}

const char* SystemException::what() const noexcept {
  return strerror(error);
}

}
