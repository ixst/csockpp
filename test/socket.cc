#include "csockpp/socket.hh"

#include "gtest/gtest.h"

#include "csockpp/socket_impl.hh"
#include "csockpp/exception.hh"
#include "csockpp/inet4_address.hh"


using namespace csockpp;

class NoThrowSocketImpl : public SocketImpl {
public:
  NoThrowSocketImpl(int descriptor) noexcept
      : SocketImpl(descriptor)
  {}

  NoThrowSocketImpl() noexcept 
      : NoThrowSocketImpl(1)
  {}

public:
  SocketImpl* clone() const noexcept {
    return new NoThrowSocketImpl(descriptor);
  }

public:
  bool CloseImpl() noexcept override {
    return true;
  }

  bool BindImpl(const Address& address) noexcept override {
    return true;
  }

};

TEST(ISocket, destructor) {
  ISocket* socket = new Socket(1);
  delete socket;
}

TEST(Socket, constructor) {
  Socket socket(1);
  EXPECT_EQ(socket.descriptor, 1);
}

TEST(Socket, copy_constructor) {
  Socket socket(1);
  Socket copied_socket(socket);
  EXPECT_EQ(copied_socket.descriptor, 1);

}

TEST(Socket, move_constructor) {
  Socket socket(1);
  Socket moved_socket(std::move(socket));
  EXPECT_EQ(moved_socket.descriptor, 1);
}

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
        Socket socket(-1);
        socket.Close();
      }, 
      SocketCloseException
  );
}

TEST(Socket, no_throw_in_close) {
  EXPECT_NO_THROW(
      {
        Socket socket(new NoThrowSocketImpl());
        socket.Close();
      }
  );
}

TEST(Socket, throw_in_bind) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        Inet4Address address("127.0.0.1", 80);
        socket.Bind(address);
      },
      SocketBindException
  );
}

TEST(Socket, no_throw_in_bind) {
  EXPECT_NO_THROW(
      {
        Socket socket(new NoThrowSocketImpl());
        Inet4Address address("127.0.0.1", 80);
        socket.Bind(address);
      }
  );
}
