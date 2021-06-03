#ifndef MY_MUTEX_H
#define MY_MUTEX_H

class My_mutex {
private:
public:

  My_mutex();

  void lock();

  void unlock();
};

#endif // MY_MUTEX_H
