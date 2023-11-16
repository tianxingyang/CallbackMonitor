#ifndef CALLBACK_MONITOR_H
#define CALLBACK_MONITOR_H

#include <sys/timerfd.h>

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "singleton.h"

namespace vito_cm {

class CallbackSentinel {
 public:
  using CondFunc = std::function<bool(uint64_t)>;
  CallbackSentinel(CondFunc&& condition);
  ~CallbackSentinel() {
    if (auto const end_time_point{std::chrono::high_resolution_clock::now()};
        condition_((end_time_point - start_time_point_).count())) {
      // TODO
      std::cout << "callback end, use: ";
    }
  }

 private:
  std::chrono::high_resolution_clock::time_point start_time_point_{std::chrono::high_resolution_clock::now()};
  CondFunc condition_;
};

class CallbackMonitor : public Singleton<CallbackMonitor> {
 public:
  using OnTimer = std::function<void()>;
  int Init();

  void StartMonitor();

  CallbackSentinel Add(std::chrono::milliseconds timeout, OnTimer&& on_timer);

 private:
  class Timer {
   public:
   private:
    int fd_;
    std::function<void()> on_timer_;
  };

  int epoll_fd_{-1};
  std::atomic_bool running_{false};
  int cur_timer_fd_{-1};
  std::thread loop_thread_;
};
}  // namespace vito_cm

#endif