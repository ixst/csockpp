#include "csockpp/exception.hh"

#include "gtest/gtest.h"


using namespace csockpp;

TEST(Exception, what) {
  int error = 1;
  SystemException exception(error);
  EXPECT_EQ(exception.error, error);
  EXPECT_EQ(exception.what(), strerror(error));
}
