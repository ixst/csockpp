#include <iostream>

#include <thread>

#include "csockpp/socket.hh"
#include "csockpp/exception.hh"
#include "csockpp/inet4_address.hh"


using namespace csockpp;

int main(int argc, char** argv) {
  char recv_buf[8192];
  std::string request = 
      "GET / HTTP/1.1\r\n"
      "Host: example.com\r\n"
      "Connection: Keep-Alive\r\n\r\n";

  Socket socket(
      AddressFamily::kInet,
      Type::kStream,
      Protocol::kTcp
  );
  Inet4Address address("93.184.216.34", 80);
  try {
    socket.Connect(address);
    std::thread recv_thread([&] {
      while (true) {
        auto recv_len = socket.Recv(recv_buf, 8192);
        if (recv_len == 0) {
          break;
        }
        std::cout << "receive succeed, len: " << recv_len << std::endl;
        std::cout << std::string(recv_buf, recv_buf + recv_len) << std::endl;
      }
    });
    std::thread send_thread([&] {
      auto sent_len = socket.Send(request.data(), request.size());
      std::cout << "send succeed, len: " << sent_len << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(3));
      socket.Shutdown();
      socket.Close();
      std::cout << "close succeed" << std::endl;
    });
    send_thread.join();
    recv_thread.join();
  } catch (const SocketConnectException& e) {
    std::cout << "failed to connect, " << e.what() << std::endl;
  } catch (const SocketSendException& e) {
    std::cout << "failed to send, " << e.what() << std::endl;
  } catch (const SocketRecvException& e) {
    std::cout << "failed to recv, " << e.what() << std::endl;
  }
  return 0;
}
