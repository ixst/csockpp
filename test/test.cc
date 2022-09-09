#include "gtest/gtest.h"
#include "csockpp/csockpp.hh"


using namespace testing;

int main(int argc, char** argv) {
  InitGoogleTest(&argc, argv);
  HelloWorld();
  return RUN_ALL_TESTS();
}
