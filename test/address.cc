#include <cstring>

#include "netinet/in.h"

#include "gtest/gtest.h"
#include "csockpp/address.hh"


using namespace csockpp;

TEST(Address, constructor) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;

  Address address(&addr, sizeof(addr));
  EXPECT_EQ(address.size, sizeof(addr));
  EXPECT_EQ(address.family, AddressFamily::kInet);
  EXPECT_EQ(std::memcmp(&address, &addr, sizeof(addr)), 0);
}
