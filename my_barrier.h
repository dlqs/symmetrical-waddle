#ifndef MY_BARRIER_H
#define MY_BARRIER_H

class My_barrier {
private:
public:
  My_barrier(int initial);

  void arrive_and_wait();

};

#endif // MY_BARRIER_H
