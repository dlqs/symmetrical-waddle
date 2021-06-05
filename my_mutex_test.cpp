//#include "my_mutex.h"
#include <atomic>
#include <thread>
#include <iostream>
#define ROUNDS 1000
#define NUM_THREADS 100


std::atomic<bool> locked(false);
int sum = 0;

void lock() {
  bool expected = false;
  while (!locked.compare_exchange_strong(expected, true))
    ;
}

void unlock() {
  locked = false;
}

void thinking(int my_id) {
  for (int i = 0; i < ROUNDS; i++) {
    lock();
    sum++;
    unlock();
  }
}

int main() {
  std::thread t[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    t[i] = std::thread(thinking, i);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    t[i].join();
  }
  std::cout << "sum :" << sum << " expected: " << ROUNDS * NUM_THREADS << std::endl;
}
