#include "csockpp/inet6_address.hh"

#include <arpa/inet.h>

#include <cstring>

#include "gtest/gtest.h"

#include "csockpp/exception.hh"


namespace csockpp {
namespace inet6_address {

std::string mock_ip = "::1";
uint16_t mock_port = 80;
uint32_t mock_flowinfo = 1;
uint32_t mock_scope_id = 1;

TEST(Inet6Address, constructor_ip_port) {
  Inet6Address address(mock_ip, mock_port, mock_flowinfo, mock_scope_id);

  struct sockaddr_in6 addr = {};
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(mock_port);
  addr.sin6_flowinfo = mock_flowinfo;
  addr.sin6_scope_id = mock_scope_id;
  inet_pton(AF_INET6, mock_ip.c_str(), &addr.sin6_addr);
  EXPECT_EQ(std::memcmp(&address.addr, &addr, sizeof(addr)), 0);
}

TEST(Inet6Address, constructor_sockaddr_in) {
  struct sockaddr_in6 addr = {};
  Inet6Address address(addr);
  EXPECT_EQ(std::memcmp(&address.addr, &addr, sizeof(addr)), 0);
}

TEST(Inet6Address, throw_in_constructor) {
  EXPECT_THROW(
      {
        Inet6Address address("test", 0);
      },
      IpParseException
  );
}

TEST(Inet6Address, set_port) {
  int port = 81;
  Inet6Address address(mock_ip, mock_port);
  address.port(port);
  
  EXPECT_EQ(address.port(), port);
}

TEST(Inet6Address, set_ip) {
  std::string ip = "::2";
  Inet6Address address(mock_ip, mock_port);
  address.ip(ip);
  
  EXPECT_EQ(address.ip(), ip);
}

TEST(Inet6Address, set_flowinfo) {
  Inet6Address address(mock_ip, mock_port, mock_flowinfo);
  address.flowinfo(2);
  
  EXPECT_EQ(address.flowinfo(), 2);
}

TEST(Inet6Address, set_scope_id) {
  Inet6Address address(mock_ip, mock_port, mock_flowinfo, mock_scope_id);
  address.scope_id(2);
  
  EXPECT_EQ(address.scope_id(), 2);
}

TEST(Inet6Address, throw_in_set_ip) {
  EXPECT_THROW(
      {
        Inet6Address address(mock_ip, mock_port);
        address.ip("test");
      },
      IpParseException
  );
}

TEST(Inet6Address, str) {
  EXPECT_EQ(Inet6Address(mock_ip, mock_port).str(), "[::1]:80");
}

TEST(Inet6Address, operator_equal_to_sockaddr) {
  struct sockaddr_in6 addr = {};
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(mock_port);
  addr.sin6_flowinfo = mock_flowinfo;
  addr.sin6_scope_id = mock_scope_id;
  inet_pton(AF_INET, mock_ip.c_str(), &addr.sin6_addr);

  EXPECT_EQ(Inet6Address(mock_ip, mock_port), addr);
}

}
}
