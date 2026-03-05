#include "ChatClient.h"

#include <iostream>
#include <format>
#include <thread>
#include <chrono>

using namespace std;

ChatClient::ChatClient(const string &ip, const string &port,
                       const string &client_name) : socket_() {
  // Retry connection loop
  while (!socket_) {
    try {
      socket_ = std::make_unique<Socket>(ip, port);
      cout << "Successfully connected to server!" << endl;
    } catch (const exception &e) {
      cout << format("Failed to connect to server: {}", e.what()) << endl;
      cout << format("Retrying in {} seconds...", retry_delay_seconds_) << endl;
      this_thread::sleep_for(chrono::seconds(retry_delay_seconds_));
    }
  }

  // Add client to the poll list
  pollfd client_pfd{};
  client_pfd.fd = socket_->get_socket_fd();
  client_pfd.events = POLLIN;
  client_pfd.revents = 0;
  pfds_.push_back(client_pfd);

  // Add standard input to the poll list
  pollfd stdin_pfd;
  stdin_pfd.fd = STDIN_FILENO;
  stdin_pfd.events = POLLIN;
  stdin_pfd.revents = 0;
  pfds_.push_back(stdin_pfd);

  // Send client name
  client_name_ = client_name;
  vector<uint8_t> client_name_data(client_name_.begin(), client_name_.end());
  socket_->send_data(client_name_data);
}

void ChatClient::run() {
  while (true) {
    // Poll for events on the pfds. Will sleep until an event happens.
    int poll_count = poll(pfds_.data(), pfds_.size(), -1);
    if (poll_count == -1) {
      throw runtime_error("poll");
    }

    // Check if the client is ready to read
    if (pfds_[0].revents & (POLLIN | POLLHUP)) {
      // Handle message from server
      vector<uint8_t> received_data = socket_->receive_data();
      string received_msg = string(received_data.begin(), received_data.end());
      // receive message
      cout << "\r\033[K" << received_msg << endl; // Clear the line
      cout << "You: " << flush; // Print received message
    }

    // Check if STDIN received events
    if (pfds_[1].revents & (POLLIN)) {
      string msg;
      cout << "You: ";
      getline(cin, msg);
      if (!msg.empty()) {
        // Send message
        vector<uint8_t> msg_data(msg.begin(), msg.end());
        socket_->send_data(msg_data);
      }
    }
  }
}