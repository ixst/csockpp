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
    return false;
  }

};

class NoThrowInCloseSocketImpl : public SocketImpl {
public:
  NoThrowInCloseSocketImpl() noexcept 
      : SocketImpl(0)
  {}

public:
  bool CloseImpl() noexcept override {
    return true;
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
        Socket socket(new ThrowInCloseSocketImpl());
        socket.Close();
      }, 
      SocketCloseException
  );
}

TEST(Socket, no_throw_in_close) {
  EXPECT_NO_THROW(
      {
        ISocket* socket = new Socket(new NoThrowInCloseSocketImpl());
        socket->Close();
        delete socket;
      }
  );
}
