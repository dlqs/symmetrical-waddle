#include "my_mutex.h"

My_mutex::My_mutex() { locked = false; }

void My_mutex::lock() {
  bool expected = false;
  while (!locked.compare_exchange_strong(expected, true)) {
    expected = false;
  }
}

void My_mutex::unlock() {
  locked = false;
}
