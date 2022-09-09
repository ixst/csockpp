#include "csockpp/address.hh"

#include <cstring>

#include <netinet/in.h>


namespace csockpp {

namespace address_internal {

auto* NewBuffer(uint8_t* data, decltype(sizeof(0)) size) noexcept {
  auto* buffer = new uint8_t[size];
  std::memcpy(buffer, data, size);
  return buffer;
}

const AddressFamily& GetAddressFamily(void* data) {
  auto* sa_family = &static_cast<sockaddr*>(data)->sa_family;
  return (const AddressFamily&)(*sa_family);
}

}

Address::Address(void* data, decltype(sizeof(0)) size) noexcept
    : size(static_cast<socklen_t>(size)),
      family(address_internal::GetAddressFamily(data)),
      buffer_(address_internal::NewBuffer((uint8_t*)data, size))
{}

Address::~Address() noexcept {
  delete[] buffer_;
}

sockaddr* const Address::operator&() const noexcept {
  return (sockaddr*)buffer_;
}

}
