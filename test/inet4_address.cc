#include "csockpp/inet4_address.hh"

#include <arpa/inet.h>

#include <cstring>

#include "gtest/gtest.h"

#include "csockpp/exception.hh"


namespace csockpp {
namespace inet4_address {

std::string mock_ip = "127.0.0.1";
uint16_t mock_port = 80;

TEST(Inet4Address, constructor_ip_port) {
  Inet4Address address(mock_ip, mock_port);

  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(mock_port);
  inet_pton(AF_INET, mock_ip.c_str(), &addr.sin_addr);
  EXPECT_EQ(std::memcmp(&address.addr, &addr, sizeof(addr)), 0);
}

TEST(Inet4Address, constructor_sockaddr_in) {
  struct sockaddr_in addr = {};
  Inet4Address address(addr);
  EXPECT_EQ(std::memcmp(&address.addr, &addr, sizeof(addr)), 0);
}

TEST(Inet4Address, throw_in_constructor) {
  EXPECT_THROW(
      {
        Inet4Address address("test", 0);
      },
      IpParseException
  );
}

TEST(Inet4Address, set_port) {
  int port = 81;
  Inet4Address address(mock_ip, mock_port);
  address.port(port);
  
  EXPECT_EQ(address.port(), port);
}

TEST(Inet4Address, set_ip) {
  std::string ip = "127.0.0.2";
  Inet4Address address(mock_ip, mock_port);
  address.ip(ip);
  
  EXPECT_EQ(address.ip(), ip);
}

TEST(Inet4Address, throw_in_set_ip) {
  EXPECT_THROW(
      {
        Inet4Address address(mock_ip, mock_port);
        address.ip("test");
      },
      IpParseException
  );
}

TEST(Inet4Address, str) {
  EXPECT_EQ(Inet4Address(mock_ip, mock_port).str(), "127.0.0.1:80");
}

TEST(Inet4Address, stream_out) {
  std::stringstream sout;
  sout << Inet4Address(mock_ip, mock_port);
  EXPECT_EQ(sout.str(), "127.0.0.1:80");
}

TEST(Inet4Address, operator_equal_to_sockaddr) {
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(mock_port);
  inet_pton(AF_INET, mock_ip.c_str(), &addr.sin_addr);

  EXPECT_EQ(Inet4Address(mock_ip, mock_port), addr);
}

}
}
