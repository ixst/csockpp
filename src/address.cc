#include "csockpp/address.hh"

#include <netinet/in.h>

#include <cstring>


namespace csockpp {

namespace address_internal {

auto* NewBuffer(uint8_t* data, decltype(sizeof(0)) size) noexcept {
  auto* buffer = new uint8_t[size];
  std::memcpy(buffer, data, size);
  return buffer;
}

AddressFamily& GetAddressFamily(void* data) {
  auto* sa_family = &static_cast<sockaddr*>(data)->sa_family;
  return (AddressFamily&)(*sa_family);
}

}

Address::Address(void* data, decltype(sizeof(0)) size) noexcept
    : data_(address_internal::NewBuffer((uint8_t*)data, size)),
      size(static_cast<socklen_t>(size)),
      family(address_internal::GetAddressFamily(data)),
      addr((struct sockaddr&)*data_)
{}

Address::~Address() noexcept {
  delete[] data_;
}

bool Address::operator==(const Address& address) const noexcept {
  if(size != address.size) {
    return false;
  }
  return !std::memcmp(data_, address.data_, size);
}

}
