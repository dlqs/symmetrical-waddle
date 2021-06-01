#include <condition_variable>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <random>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int index = 0;

sem_t full, empty;
std::mutex queue_mutex;

std::condition_variable m_waitcond;
std::mutex m_mux;
int m_value;

void sem_wait() {
  // This locks the mutex until it is destroyed at method exit.
  std::unique_lock<std::mutex> lck(m_mux);

  // Check the mutex value, and wait if need be.
  if (--m_value < 0) {
    // Make us wait.  When we wait, the mutex is unlocked until the
    // wait ends.
    m_waitcond.wait(lck);
  }
}

void sem_post() {
  // This locks the mutex until it is destroyed at method exit.
  std::unique_lock<std::mutex> lck(m_mux);

  // Start a waiting thread if required.
  if (++m_value <= 0)
    m_waitcond.notify_one();
}

void *produce(void *arg) {
  while (1) {
    sleep(1);
    sem_wait(&empty);
    queue_mutex.lock();
    int item = rand() % 100;
    buffer[index++] = item;
    cout << "Produced " << item << endl;
    queue_mutex.unlock();
    sem_post(&full);
  }
}

void *consume(void *arg) {
  while (1) {
    sleep(1);
    sem_wait(&full);
    queue_mutex.lock();
    int item = buffer[--index];
    cout << "Consumed " << item << endl;
    queue_mutex.unlock();
    sem_post(&empty);
  }
}

int main() {
  pthread_t producer, consumer;
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  pthread_create(&producer, NULL, produce, NULL);
  pthread_create(&consumer, NULL, consume, NULL);
  pthread_exit(NULL);
}
