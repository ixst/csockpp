#include "csockpp/socket.hh"

#include <set>
#include <functional>

#include "gtest/gtest.h"

#include "csockpp/socket_impl.hh"
#include "csockpp/exception.hh"
#include "csockpp/address.hh"
#include "csockpp/inet4_address.hh"


using namespace csockpp;

class MockSocketImpl : public SocketImpl {
public:
  std::function<bool()> close_impl;
  std::function<bool(const Address& address)> bind_impl;
  std::function<bool(const int& backlog)> listen_impl;
  std::function<int(const Address& address)> connect_impl;
  std::function<int(
      Address& address, 
      const std::set<Flag::Sock>& flags
  )> accept_impl;
  std::function<ssize_t(
      const void* buffer, 
      const size_t& size,
      const std::set<Flag::Msg>& flags
  )> send_impl;


public:
  MockSocketImpl(int descriptor) noexcept
      : SocketImpl(descriptor)
  {}

  MockSocketImpl() noexcept 
      : MockSocketImpl(1)
  {}

public:
  SocketImpl* clone() const noexcept {
    return new MockSocketImpl(descriptor);
  }

public:
  bool CloseImpl() noexcept override {
    if (close_impl) {
      return close_impl();
    }
    return true;
  }

  bool BindImpl(const Address& address) noexcept override {
    if (bind_impl) {
      return bind_impl(address);
    }
    return true;
  }

  bool ListenImpl(const int& backlog) noexcept override {
    if (listen_impl) {
      return listen_impl(backlog);
    }
    return true;
  }

  int ConnectImpl(const Address& address) noexcept override {
    if (connect_impl) {
      return connect_impl(address);
    }
    return 0;
  }

  int AcceptImpl(
      Address& address, 
      const std::set<Flag::Sock>& flags
  ) noexcept override {
    if (accept_impl) {
      return accept_impl(address, flags);
    }
    return 0;
  }

  ssize_t SendImpl(
      const void* buffer,
      const size_t& size,
      const std::set<Flag::Msg>& flags
  ) noexcept override {
    if (send_impl) {
      return send_impl(buffer, size, flags);
    }
    return 0;
  }

};

TEST(ISocket, virtual_destructor) {
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

TEST(Socket, constructor_throw) {
  EXPECT_THROW(
      {
        Socket socket(AddressFamily::kInet, Type::kStream, Protocol::kUdp);
      }, 
      SocketOpenException
  );
}

TEST(Socket, close_throw) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        socket.Close();
      }, 
      SocketCloseException
  );
}

TEST(Socket, close_no_throw) {
  EXPECT_NO_THROW(
      {
        Socket socket(new MockSocketImpl());
        socket.Close();
      }
  );
}

TEST(Socket, bind_throw) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        Inet4Address address("127.0.0.1", 80);
        socket.Bind(address);
      },
      SocketBindException
  );
}

TEST(Socket, bind_no_throw) {
  EXPECT_NO_THROW(
      {
        Socket socket(new MockSocketImpl());
        Inet4Address address("127.0.0.1", 80);
        socket.Bind(address);
      }
  );
}

TEST(Socket, listen_throw) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        socket.Listen();
      },
      SocketListenException
  );
}

TEST(Socket, listen_no_throw) {
  EXPECT_NO_THROW(
      {
        Socket socket(new MockSocketImpl());
        socket.Listen();
      }
  );
}

TEST(Socket, connect_no_throw) {
  EXPECT_NO_THROW(
      {
        Socket socket(new MockSocketImpl());
        Inet4Address address("127.0.0.1", 80);
        socket.Connect(address);
      }
  );
}

TEST(Socket, connect_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl();
        socket_impl->connect_impl = 
            [&](const Address& address) -> int {
              return -2;
            };
        Socket socket(socket_impl);
        Inet4Address address("127.0.0.1", 80);
        socket.Connect(address);
      }, 
      SocketNonblockingException
  );
}

TEST(Socket, connect_throw_connection_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        Inet4Address address("127.0.0.1", 80);
        socket.Connect(address);
      },
      SocketConnectException
  );
}

TEST(Socket, accept_no_throw) {
  auto* socket_impl = new MockSocketImpl();
  socket_impl->accept_impl = 
      [&](Address& address, const std::set<Flag::Sock>& flags) -> int {
        return 1;
      };
  Socket socket(socket_impl);
  Inet4Address address("127.0.0.1", 80);
  auto accepted = socket.Accept(address);
  EXPECT_EQ(accepted.descriptor, 1);
}

TEST(Socket, accept_throw_connect_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        Inet4Address address("127.0.0.1", 80);
        socket.Accept(address);
      },
      SocketConnectException
  );
}


TEST(Socket, accept_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl();
        socket_impl->accept_impl = 
            [&](Address& address, const std::set<Flag::Sock>& flags) -> int {
              return -2;
            };
        Socket socket(socket_impl);
        Inet4Address address("127.0.0.1", 80);
        socket.Accept(address);
      },
      SocketNonblockingException
  );
}

TEST(Socket, send_no_throw) {
  auto* socket_impl = new MockSocketImpl();
  socket_impl->send_impl = 
      [&](
          const void* buffer, 
          size_t size, 
          const std::set<Flag::Msg>& flags
      ) -> ssize_t {
        return size;
      };
  Socket socket(socket_impl);
  char buffer[1];
  auto sent_size = socket.Send(buffer, 1);
  EXPECT_EQ(socket.descriptor, sent_size);
}

TEST(Socket, send_throw_connect_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        char buffer[1];
        socket.Send(buffer, 1);
      },
      SocketSendException
  );
}

TEST(Socket, send_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl();
        socket_impl->send_impl = 
            [&](
                const void* buffer, 
                const size_t& size, 
                const std::set<Flag::Msg>& flags
            ) -> ssize_t {
              return -2;
            };
        Socket socket(socket_impl);
        char buffer[1];
        socket.Send(buffer, 1);
      },
      SocketNonblockingException
  );
}
