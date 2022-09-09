#include <errno.h>

#include "gtest/gtest.h"
#include "csockpp/socket.hh"
#include "csockpp/socket_impl.hh"
#include "csockpp/exception.hh"


using namespace csockpp;

class ThrowInCloseSocketImpl : public SocketImpl {
public:
  ThrowInCloseSocketImpl() noexcept 
      : SocketImpl(0)
  {}

public:
  bool CloseImpl() noexcept override {
    errno = 1;
    return false;
  }

};

TEST(Socket, throw_in_constructor) {
  EXPECT_THROW(
      {
        Socket socket(AddressFamily::kInet, Type::kStream, Protocol::kUdp);
      }, 
      SocketOpenException
  );
}

TEST(Socket, throw_in_close) {
  EXPECT_THROW(
      {
        try {
          Socket socket(new ThrowInCloseSocketImpl());
          socket.Close();
        } catch (const SocketCloseException& e) {
          EXPECT_EQ(e.what(), strerror(1));
          throw e;
        }
      }, 
      SocketCloseException
  );
}

TEST(Socket, constructor) {
}
