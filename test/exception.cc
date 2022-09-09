#include "gtest/gtest.h"
#include "csockpp/exception.hh"


using namespace csockpp;

TEST(Exception, what) {
  int error = 1;
  SocketException exception(error);
  EXPECT_EQ(exception.error, error);
  EXPECT_EQ(exception.what(), strerror(error));
}
