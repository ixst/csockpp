#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <list>

#include "csockpp/socket.hh"
#include "csockpp/exception.hh"
#include "csockpp/inet4_address.hh"


using namespace csockpp;

const Inet4Address server_address("127.0.0.1", 8000);


Socket CreateServerSocket() {
  Socket socket(
      AddressFamily::kInet,
      Type::kStream,
      Protocol::kTcp
  );
  socket.Bind(server_address);
  socket.Listen();
  return socket;
}

class FdSet {
public:
  FdSet() noexcept {
    Zero();
  }

public:
  fd_set& fds() noexcept {
    return fds_;
  }

  const int& last_fd() const noexcept {
    return last_fd_;
  }

public:
  void Zero() noexcept {
    last_fd_ = 0;
    FD_ZERO(&fds_);
  }

  void Set(const Socket& socket) noexcept {
    Set(socket.descriptor);
  }
  
  void Set(int fd) noexcept {
    if(last_fd_ < fd) {
      last_fd_ = fd;
    }
    FD_SET(fd, &fds_);
  }

  void Clear(const Socket& socket) noexcept {
    Clear(socket.descriptor);
  }

  void Clear(int fd) noexcept {
    FD_CLR(fd, &fds_);
  }

  bool IsSet(const Socket& socket) noexcept {
    return IsSet(socket.descriptor);
  };

  bool IsSet(int fd) noexcept {
    return FD_ISSET(fd, &fds_);
  };

private:
  fd_set fds_;
  int last_fd_;

};

class Server {
public:
  Server() 
      : socket_(CreateServerSocket()),
        thread_(
            [&] {
              Run();
            }
        )
  {}

public: 
  void Stop() {
    socket_.Shutdown();
    socket_.Close();
    thread_.join();
  }

private:
  Socket socket_;
  std::thread thread_;

  std::list<Socket> accepteds_;

private:
  FdSet fd_set() noexcept {
    FdSet fds;
    fds.Set(socket_);
    for (const auto& accepted : accepteds_) {
      fds.Set(accepted);
    }
    return fds;
  }
 
private:
  void Run() noexcept {
    while (true) {
      auto read_fds = fd_set();
      select(read_fds.last_fd() + 1, &read_fds.fds(), nullptr, nullptr, nullptr);
      if (read_fds.IsSet(socket_)) {
        try {
          Socket accepted = Accept();
          accepteds_.push_back(accepted);
        } catch (const SocketAcceptException& e) {
          for (const auto& accepted : accepteds_) {
            accepted.Shutdown();
            accepted.Close();
          }
          return;
        }
      }
      auto it = accepteds_.begin();
      for (; it != accepteds_.end();) {
        const auto& accepted = *it;
        if (read_fds.IsSet(accepted)) {
          try {
            OnReceive(accepted);
          } catch (const SocketRecvException& e) {
            try {
              accepted.Shutdown();
              accepted.Close();
              it = accepteds_.erase(it);
            } catch (const std::exception& e) {
              std::cout << "failed to shutdown " << e.what() << std::endl;
            }
            continue;
          }
        }
        it++;
      }
    }
  }
 
  void OnReceive(Socket socket) {
    std::array<char, 8192> buf;
    auto recv_len = socket.Recv(buf.data(), buf.size());
    std::string recv_msg(buf.data(), buf.data() + recv_len);
    std::cout << "server << " << recv_msg << std::endl;
    std::cout << "server >> " << recv_msg << std::endl;
    socket.Send(recv_msg.data(), recv_msg.size());
  }

  Socket Accept() {
    Inet4Address address;
    return socket_.Accept(address);
  }

};


int main(int argc, char** argv) {
  try {
    Server server;
    Socket client(
        AddressFamily::kInet,
        Type::kStream,
        Protocol::kTcp
    );
    client.Connect(server_address);

    while (true) {
      std::string in;
      std::cout << "client >> ";
      std::cin >> in;
      if (in == ".exit") {
        client.Shutdown();
        client.Close();
        server.Stop();
        break;
      } else {
        client.Send(in.data(), in.size());
        std::array<char, 8192> buf;
        auto recv_len = client.Recv(buf.data(), buf.size());
        std::string recv_msg(buf.data(), buf.data() + recv_len);
        std::cout << "client << " << recv_msg << std::endl;
      }
    }   
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
