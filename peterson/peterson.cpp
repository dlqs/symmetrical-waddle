#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5
#define NUM_ADDS 100

void *PrintHello(void *threadid) {
  long tid;
  tid = (long)threadid;
  cout << "Hello World! Thread ID, " << tid << endl;
  pthread_exit(NULL);
}

int sum = 0;

// begin: lock/unlock global variables
int flag[2];
int turn;
// end

// Fill in:
void lock_init() {
  // Initialize lock by reseting the desire of
  // both the threads to acquire the locks.
  // And, giving turn to one of them.
  flag[0] = flag[1] = 0;
  turn = 0;
}

// Fill in:
void lock(int myid) {
  // Set flag[self] = 1 saying you want to acquire lock
  flag[myid] = 1;

  // But, first give the other thread the chance to
  // acquire lock
  turn = 1 - myid;

  // Wait until the other thread looses the desire
  // to acquire lock or it is your turn to get the lock.
  while (flag[1 - myid] == 1 && turn == 1 - myid);
}

// Fill in:
void unlock(int myid) {
  // You do not desire to acquire lock in future.
  // This will allow the other thread to acquire
  // the lock.
  flag[myid] = 0;
}

void *adder(void *threadid) {
  int myid = (long)threadid;
  for (int i = 0; i < 100; i++) {
    lock(myid);
    sum++;
    unlock(myid);
  }
}

int main() {
  pthread_t threads[NUM_THREADS];
  int rc;
  int i;
  lock_init();

  // Kick off threads
  for (i = 0; i < NUM_THREADS; i++) {
    cout << "main() : creating thread, " << i << endl;
    rc = pthread_create(&threads[i], NULL, adder, (void *)i);
    if (rc) {
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
    }
  }

  // Wait for threads to finish
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  cout << "Actual sum: " << sum << " Expected sum: " << NUM_THREADS * NUM_ADDS << endl;
  pthread_exit(NULL);
}
