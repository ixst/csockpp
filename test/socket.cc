#include "csockpp/socket.hh"

#include <set>
#include <cstring>
#include <functional>

#include "gtest/gtest.h"

#include "csockpp/socket_impl.hh"
#include "csockpp/exception.hh"
#include "csockpp/address.hh"
#include "csockpp/inet4_address.hh"
#include "csockpp/inet6_address.hh"


using namespace csockpp;

class MockSocketImpl : public SocketImpl {
public:
  std::function<bool(
      const int& descriptor,
      const int& how
  )> shutdown_impl;
  std::function<bool(const int& descriptor)> close_impl;
  std::function<bool(
      const int& descriptor,
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  )> bind_impl;
  std::function<bool(
      const int& descriptor, 
      const int& backlog
  )> listen_impl;
  std::function<int(
      const int& descriptor,
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  )> connect_impl;
  std::function<int(
      const int& descriptor,
      struct sockaddr* addr, 
      socklen_t* addr_len,
      const int& flags
  )> accept_impl;
  std::function<ssize_t(
      const int& descriptor,
      const void* buffer, 
      const size_t& buffer_len,
      const int& flags
  )> send_impl;
  std::function<ssize_t(
      const int& descriptor,
      void* buffer, 
      const size_t& buffer_len,
      const int& flags
  )> recv_impl;
  std::function<ssize_t(
      const int& descriptor,
      const void* buffer, 
      const size_t& buffer_len,
      const int& flags,
      const struct sockaddr* addr,
      const socklen_t& addr_len
  )> sendto_impl;
  std::function<ssize_t(
      const int& descriptor,
      void* buffer, 
      const size_t& buffer_len,
      const int& flags,
      struct sockaddr* addr,
      socklen_t* addr_len
  )> recvfrom_impl;


public:
  MockSocketImpl(int descriptor) noexcept
      : SocketImpl(descriptor)
  {}

public:
  SocketImpl* CloneImpl(int descriptor) const noexcept {
    return new MockSocketImpl(descriptor);
  }

  bool ShutdownImpl(
      const int& descriptor, 
      const int& how
  ) const noexcept override {
    if (shutdown_impl) {
      return shutdown_impl(descriptor, how);
    }
    return true;
  }
  bool CloseImpl(const int& descriptor) const noexcept override {
    if (close_impl) {
      return close_impl(descriptor);
    }
    return true;
  }

  bool BindImpl(
      const int& descriptor,
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept override {
    if (bind_impl) {
      return bind_impl(descriptor, addr, addr_len);
    }
    return true;
  }

  bool ListenImpl(
      const int& descriptor, 
      const int& backlog
  ) const noexcept override {
    if (listen_impl) {
      return listen_impl(descriptor, backlog);
    }
    return true;
  }

  int ConnectImpl(
      const int& descriptor,
      const struct sockaddr* addr, 
      const socklen_t& addr_len
  ) const noexcept override {
    if (connect_impl) {
      return connect_impl(descriptor, addr, addr_len);
    }
    return 0;
  }

  int AcceptImpl(
      const int& descriptor,
      struct sockaddr* addr, 
      socklen_t* addr_len,
      const int& flags
  ) const noexcept override {
    if (accept_impl) {
      return accept_impl(descriptor, addr, addr_len, flags);
    }
    return 0;
  }

  ssize_t SendImpl(
      const int& descriptor,
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags
  ) const noexcept override {
    if (send_impl) {
      return send_impl(descriptor, buffer, buffer_len, flags);
    }
    return 0;
  }

  ssize_t RecvImpl(
      const int& descriptor,
      void* buffer,
      const size_t& buffer_len, 
      const int& flags
  ) const noexcept override {
    if (recv_impl) {
      return recv_impl(descriptor, buffer, buffer_len, flags);
    }
    return 0;
  }

  ssize_t SendToImpl(
      const int& descriptor,
      const void* buffer,
      const size_t& buffer_len, 
      const int& flags,
      const struct sockaddr* addr,
      const socklen_t& addr_len
  ) const noexcept override {
    if (sendto_impl) {
      return sendto_impl(
          descriptor, 
          buffer, 
          buffer_len, 
          flags, 
          addr, 
          addr_len
      );
    }
    return 0;
  }

  ssize_t RecvFromImpl(
      const int& descriptor,
      void* buffer,
      const size_t& buffer_len, 
      const int& flags,
      struct sockaddr* addr,
      socklen_t* addr_len
  ) const noexcept override {
    if (recvfrom_impl) {
      return recvfrom_impl(
          descriptor, 
          buffer, 
          buffer_len, 
          flags, 
          addr, 
          addr_len
      );
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

TEST(Socket, shutdown_no_throw) {
  EXPECT_NO_THROW(
      {
        auto* socket_impl = new MockSocketImpl(2);
        socket_impl->shutdown_impl = 
            [&](const auto& descriptor, const auto& how) -> bool {
              EXPECT_EQ(descriptor, 2);
              EXPECT_EQ(how, SHUT_RDWR);
              return true;
            };
        Socket socket(socket_impl);
        socket.Shutdown();
      }
  );
}

TEST(Socket, shutdown_throw) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        socket.Shutdown();
      }, 
      SocketShutdownException
  );
}

TEST(Socket, shutdown_with_how_no_throw) {
  EXPECT_NO_THROW(
      {
        auto* socket_impl = new MockSocketImpl(2);
        socket_impl->shutdown_impl = 
            [&](const auto& descriptor, const auto& how) {
              EXPECT_EQ(descriptor, 2);
              EXPECT_EQ(how, SHUT_RD);
              return true;
            };
        Socket socket(socket_impl);
        socket.Shutdown(Flag::Shut::kRecv);
      }
  );
}

TEST(Socket, shutdown_with_how_throw) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        socket.Shutdown(Flag::Shut::kSend);
      }, 
      SocketShutdownException
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
        auto* socket_impl = new MockSocketImpl(1);
        socket_impl->close_impl =
            [&] (const auto& descriptor) -> auto {
              EXPECT_EQ(descriptor, 1);
              return true;
            };
        Socket socket(socket_impl);
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
        Inet4Address address("127.0.0.1", 80);
        auto* socket_impl = new MockSocketImpl(2);
        socket_impl->bind_impl =
            [&] (
                const auto& descriptor,
                const auto* addr, 
                const auto& addr_len
            ) -> auto {
              EXPECT_EQ(descriptor, 2);
              EXPECT_EQ(addr_len, address.size);
              EXPECT_EQ(std::memcmp(addr, &address.addr, addr_len), 0);
              return true;
            };
        Socket socket(socket_impl);
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
        auto* socket_impl = new MockSocketImpl(3);
        socket_impl->listen_impl =
            [&] (
                const auto& descriptor,
                const auto& backlog
            ) -> auto {
              EXPECT_EQ(descriptor, 3);
              EXPECT_EQ(backlog, Socket::kMaxConn);
              return true;
            };
        Socket socket(socket_impl);
        socket.Listen();
      }
  );
}

TEST(Socket, connect_no_throw) {
  EXPECT_NO_THROW(
      {
        Inet4Address address("127.0.0.1", 80);
        auto* socket_impl = new MockSocketImpl(4);
        socket_impl->connect_impl = 
            [&](
                const auto& descriptor,
                const auto* addr, 
                const auto& addr_len
            ) -> auto {
              EXPECT_EQ(descriptor, 4);
              EXPECT_EQ(addr_len, address.size);
              EXPECT_EQ(std::memcmp(addr, &address.addr, addr_len), 0);
              return 0;
            };
        Socket socket(socket_impl);
        socket.Connect(address);
      }
  );
}

TEST(Socket, connect_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        Inet4Address address("127.0.0.1", 80);
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->connect_impl = 
            [&](
                const auto& descriptor,
                const auto* addr, 
                const auto& addr_len
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
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
  auto* socket_impl = new MockSocketImpl(5);
  Inet6Address src("::1", 80);
  socket_impl->accept_impl = 
      [&](
          const auto& descriptor,
          auto* addr, 
          auto* addr_len,
          const auto& flags
      ) -> auto {
        EXPECT_EQ(descriptor, 5);
        EXPECT_EQ(
            flags,
            (
                static_cast<int>(Flag::Sock::kNonblock) | 
                static_cast<int>(Flag::Sock::kCloseOnExecute)
            )
        );
        std::memcpy(addr, &src.addr, src.size);
        *addr_len = src.size;
        return 99;
      };
  Socket socket(socket_impl);
  Inet6Address dst;
  auto accepted = socket.Accept(
      dst, 
      { Flag::Sock::kNonblock, Flag::Sock::kCloseOnExecute }
  );
  EXPECT_EQ(accepted.descriptor, 99);
  EXPECT_EQ(dst.size, src.size);
  EXPECT_EQ(std::memcmp(&dst.addr, &src.addr, src.size), 0);
}

TEST(Socket, accept_throw_accept_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        Inet4Address address;
        socket.Accept(address);
      },
      SocketAcceptException
  );
}

TEST(Socket, accept_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->accept_impl = 
            [&](
                const auto& descriptor,
                auto* addr, 
                auto* addr_len,
                const auto& flags
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
        Inet4Address address;
        socket.Accept(address);
      },
      SocketNonblockingException
  );
}

TEST(Socket, send_no_throw) {
  auto* socket_impl = new MockSocketImpl(6);
  socket_impl->send_impl = 
      [&](
          const auto& descriptor,
          const auto* buffer, 
          const auto& buffer_len, 
          const auto& flags
      ) -> ssize_t {
        EXPECT_EQ(descriptor, 6);
        EXPECT_EQ(((char*)buffer)[0], 1);
        EXPECT_EQ(((char*)buffer)[1], 2);
        EXPECT_EQ(((char*)buffer)[2], 3);
        EXPECT_EQ(((char*)buffer)[3], 4);
        EXPECT_EQ(buffer_len, 4);
        return 2;
      };
  Socket socket(socket_impl);
  char buffer[4] = { 1, 2, 3, 4 };
  auto sent_size = socket.Send(buffer, 4);
  EXPECT_EQ(sent_size, 2);
}

TEST(Socket, send_throw_send_exception) {
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
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->send_impl = 
            [&](
                const int& descriptor,
                const void* buffer, 
                const size_t& buffer_len, 
                const int& flags
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
        char buffer[1];
        socket.Send(buffer, 1);
      },
      SocketNonblockingException
  );
}

TEST(Socket, recv_no_throw) {
  auto* socket_impl = new MockSocketImpl(7);
  socket_impl->recv_impl = 
      [&](
          const auto& descriptor,
          auto* buffer, 
          const auto& buffer_len, 
          const auto& flags
      ) -> auto {
        EXPECT_EQ(descriptor, 7);
        ((char*)buffer)[0] = 2;
        EXPECT_EQ(buffer_len, 4);
        return 1;
      };
  Socket socket(socket_impl);
  char buffer[4];
  auto recv_size = socket.Recv(buffer, 4);
  EXPECT_EQ(buffer[0], 2);
  EXPECT_EQ(recv_size, 1);
}

TEST(Socket, recv_throw_recv_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        char buffer[1];
        socket.Recv(buffer, 1);
      },
      SocketRecvException
  );
}

TEST(Socket, recv_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->recv_impl = 
            [&](
                const auto& descriptor,
                auto* buffer, 
                const auto& buffer_len, 
                const auto& flags
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
        char buffer[1];
        socket.Recv(buffer, 1);
      },
      SocketNonblockingException
  );
}

TEST(Socket, sendto_no_throw) {
  Inet4Address address("127.0.0.1", 80);
  auto* socket_impl = new MockSocketImpl(8);
  socket_impl->sendto_impl = 
      [&](
          const auto& descriptor,
          const auto* buffer, 
          const auto& buffer_len, 
          const auto& flags,
          const struct sockaddr* addr,
          const socklen_t& addr_len
      ) -> ssize_t {
        EXPECT_EQ(descriptor, 8);
        EXPECT_EQ(addr_len, address.size);
        EXPECT_EQ(std::memcmp(addr, &address.addr, addr_len), 0);
        EXPECT_EQ(((char*)buffer)[0], 1);
        EXPECT_EQ(((char*)buffer)[1], 2);
        EXPECT_EQ(((char*)buffer)[2], 3);
        EXPECT_EQ(((char*)buffer)[3], 4);
        EXPECT_EQ(buffer_len, 4);
        return 3;
      };
  Socket socket(socket_impl);
  char buffer[4] = { 1, 2, 3, 4 };
  auto sent_size = socket.SendTo(buffer, 4, address);
  EXPECT_EQ(sent_size, 3);
}

TEST(Socket, sendto_throw_send_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        char buffer[1];
        Inet4Address address("127.0.0.1", 80);
        socket.SendTo(buffer, 1, address);
      },
      SocketSendException
  );
}

TEST(Socket, sendto_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->sendto_impl = 
            [&](
                const int& descriptor,
                const void* buffer, 
                const size_t& buffer_len, 
                const int& flags,
                const struct sockaddr* addr,
                const socklen_t& addr_len
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
        char buffer[1];
        Inet4Address address("127.0.0.1", 80);
        socket.SendTo(buffer, 1, address);
      },
      SocketNonblockingException
  );
}

TEST(Socket, recvfrom_no_throw) {
  Inet4Address src;
  auto* socket_impl = new MockSocketImpl(9);
  socket_impl->recvfrom_impl = 
      [&](
          const auto& descriptor,
          auto* buffer, 
          const auto& buffer_len, 
          const auto& flags,
          auto* addr,
          auto* addr_len
      ) -> auto {
        *addr_len = src.size;
        std::memcpy(addr, &src.addr, src.size);
        EXPECT_EQ(descriptor, 9);
        ((char*)buffer)[0] = 3;
        EXPECT_EQ(buffer_len, 4);
        return 2;
      };
  Socket socket(socket_impl);
  char buffer[4];
  Inet4Address dst;
  auto recv_size = socket.RecvFrom(buffer, 4, dst);
  EXPECT_EQ(buffer[0], 3);
  EXPECT_EQ(recv_size, 2);
  EXPECT_EQ(src, dst);
}

TEST(Socket, recvfrom_throw_recv_exception) {
  EXPECT_THROW(
      {
        Socket socket(-1);
        char buffer[1];
        Inet4Address address;
        socket.RecvFrom(buffer, 1, address);
      },
      SocketRecvException
  );
}

TEST(Socket, recvfrom_throw_nonblocking_exception) {
  EXPECT_THROW(
      {
        auto* socket_impl = new MockSocketImpl(0);
        socket_impl->recvfrom_impl = 
            [&](
                const auto& descriptor,
                auto* buffer, 
                const auto& buffer_len, 
                const auto& flags,
                auto* addr,
                auto* addr_len
            ) -> auto {
              return -2;
            };
        Socket socket(socket_impl);
        char buffer[1];
        Inet4Address address;
        socket.RecvFrom(buffer, 1, address);
      },
      SocketNonblockingException
  );
}
