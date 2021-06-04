#ifndef MY_MUTEX_H
#define MY_MUTEX_H
#include <atomic>

class My_mutex {
private:
  std::atomic<bool> locked;

public:

  My_mutex();

  void lock();

  void unlock();
};

#endif // MY_MUTEX_H
