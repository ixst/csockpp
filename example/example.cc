#include <iostream>

#include "csockpp/socket.hh"


int main(int argc, char** argv) {
  Socket socket(
      AddressFamily::kInet,
      Type::kStream,
      Protocol::kTcp
  );
  socket.option(Option::Tcp::kNoDelay, true);
  socket.option(Option::kReceiveBuffer, 2 * 1024 * 1024);
  bool should_no_delay = socket.option(Option::Tcp::kNoDelay);
  int receive_buffer = socket.option(Option::kReceiveBuffer);

  std::string request = 
      "GET / HTTP/1.1\r\n"
      "Host: example.com\r\n"
      "Connection: Keep-Alive\r\n\r\n";
      
  socket.Send(request.data(), request.size());
 
  char buffer[8192];
  int received_size = socket.Receive(buffer, 8192);
  std::string received_text(buffer, buffer + received_size);

  std::cout << received_text << std::endl;

  return 0;
}
