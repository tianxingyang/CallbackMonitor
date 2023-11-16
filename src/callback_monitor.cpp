#include "callback_monitor.h"

#include <sys/epoll.h>

#include <thread>

namespace vito_cm {
int CallbackMonitor::Init() {
  epoll_fd_ = epoll_create1(0);
  if (epoll_fd_ == -1) {
    perror("epoll_create1 failed");
    return -1;
  }

  running_ = true;

  loop_thread_ = std::thread{[this]() {
    epoll_event events[8];
    while (running_) {
      auto n_events = epoll_wait(epoll_fd_, events, 8, -1);

      if (n_events == -1) {
      }

      for (int i = 0; i < n_events; ++i) {
        if (events[i].data.fd == cur_timer_fd_) {
        }
      }
    }
  }};
}

void CallbackMonitor::StartMonitor() {}

void CallbackMonitor::Add(std::chrono::milliseconds timeout, OnTimer&& on_timer) {
  return CallbackMonitor{[](uint64_t) { return }};
}
}  // namespace vito_cm
