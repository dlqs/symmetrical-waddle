#include "my_mutex.h"
#include <thread>
#include <iostream>
#define ROUNDS 10000
#define NUM_THREADS 10000


My_mutex mutex;
int sum = 0;

void thinking(int my_id) {
  for (int i = 0; i < ROUNDS; i++) {
    mutex.lock();
    sum++;
    mutex.unlock();
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
