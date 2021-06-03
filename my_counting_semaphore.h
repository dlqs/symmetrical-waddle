#ifndef COUNTING_SEMAPHORE_H
#define COUNTING_SEMAPHORE_H

class My_counting_semaphore {
private:
public:
  My_counting_semaphore(int initial);

  void release();

  void acquire();

};

#endif // COUNTING_SEMAPHORE_H
