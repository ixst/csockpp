#include "csockpp/address.hh"

#include <netinet/in.h>

#include <cstring>

#include "gtest/gtest.h"


using namespace csockpp;

TEST(Address, constructor) {
  struct sockaddr_in addr;

  Address address(&addr, sizeof(addr));
  EXPECT_EQ(address.size, sizeof(addr));
  EXPECT_EQ(std::memcmp(&address.addr, &addr, sizeof(addr)), 0);
}

TEST(Address, operator_equal_to_address) {
  struct sockaddr_in addr;
  Address address1(&addr, sizeof(addr));
  Address address2(&addr, sizeof(addr));
  EXPECT_EQ(address1, address2);
}

TEST(Address, operator_not_equal_to_diff_size_address) {
  struct sockaddr_in addr;
  struct sockaddr_in6 addr6;

  Address address1(&addr, sizeof(addr));
  Address address2(&addr6, sizeof(addr6));
  EXPECT_NE(address1, address2);
}
