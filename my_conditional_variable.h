#ifndef MY_CONDITIONAL_VARIABLE_H
#define MY_CONDITIONAL_VARIABLE_H

class My_conditional_variable {
private:
public:

  My_conditional_variable();

  void wait();

  void notify_one();

  void notify_all();

};

#endif // MY_CONDITIONAL_VARIABLE_H
