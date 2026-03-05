#ifndef SUSSY_SOCKET_CHATCLIENT_H
#define SUSSY_SOCKET_CHATCLIENT_H
#include <memory>
#include <string>
#include <vector>
#include <sys/poll.h>

#include "sussy_socket/Socket.h"


class ChatClient {
public:
  ChatClient(const std::string &ip, const std::string &port,
             const std::string &client_name);
  void run();

private:
  std::unique_ptr<Socket> socket_;
  std::string client_name_;
  std::vector<pollfd> pfds_;
  const int retry_delay_seconds_ = 1;
  const int retry_count_ = 5;

};


#endif //SUSSY_SOCKET_CHATCLIENT_H