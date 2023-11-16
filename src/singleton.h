#ifndef CALLBACK_MONITOR_SINGLETON_H
#define CALLBACK_MONITOR_SINGLETON_H

namespace vito_cm {
template <typename T>
class Singleton {
 public:
  Singleton() = default;
  ~Singleton() = default;
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;

  T& Instance() {
    static T instance;
    return instance;
  }
};
}  // namespace vito_cm

#endif